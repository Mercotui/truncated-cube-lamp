#include "animation_runner.hpp"

#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include <QtCore/QLoggingCategory>
#include <QtCore/QThread>
#include <algorithm>
#include <utility>

Q_LOGGING_CATEGORY(AnimationRunnerLog, "animation.runner", QtInfoMsg)

namespace {
constexpr int kMinimumFrameIntervalMS = 16;  // for max 60 fps
constexpr std::string_view kLibrariesResourceDir = ":/libraries";
constexpr auto kClearColor = "black";

QJSValue createAnimationContext(QJSEngine *engine,
                                const QDateTime &previous_frame_time,
                                const QDateTime &current_frame_time,
                                ScreenInterfaceJs *screen) {
  auto context = engine->newObject();
  auto libs = engine->newObject();
  libs.setProperty("chroma", engine->globalObject().property("chroma"));
  context.setProperty("libs", libs);
  context.setProperty("current_frame_time",
                      engine->toScriptValue(current_frame_time));
  context.setProperty("previous_frame_time",
                      engine->toScriptValue(previous_frame_time));
  context.setProperty("screen", engine->newQObject(screen));

  return context;
}
}  // namespace

AnimationRunner::AnimationRunner(
    std::unique_ptr<ScreenControllerInterface> screen_controller)
    : QObject(),
      do_loop_(false),
      loop_timer_(new QTimer(this)),
      engine_(new QJSEngine(this)),
      screen_interface_js_(
          new ScreenInterfaceJs(screen_controller->getResolution(), this)),
      screen_(std::move(screen_controller)) {
  Q_INIT_RESOURCE(libraries);
  loadLibraries();

  engine_->installExtensions(QJSEngine::ConsoleExtension);
  loop_timer_->setSingleShot(true);
  connect(loop_timer_, &QTimer::timeout, this, &AnimationRunner::loop);
  connect(screen_interface_js_, &ScreenInterfaceJs::draw,
          [this]() { screen_->draw(screen_interface_js_->pixels()); });
}

AnimationRunner::~AnimationRunner() { Q_CLEANUP_RESOURCE(libraries); }

void AnimationRunner::loadLibraries() {
  auto website_dir = QDir(kLibrariesResourceDir.data());
  QDirIterator dir_it(website_dir.path(), {}, QDir::Files,
                      QDirIterator::Subdirectories);
  while (dir_it.hasNext()) {
    auto file_path = dir_it.next();
    auto file_path_without_resource =
        file_path.mid(kLibrariesResourceDir.size());

    QFile scriptFile(file_path);
    if (!scriptFile.open(QIODevice::ReadOnly)) {
      qCWarning(AnimationRunnerLog) << "Tried to load library" << file_path
                                    << "but could not open the file";
      continue;
    }
    qCInfo(AnimationRunnerLog)
        << "Loading library" << file_path_without_resource << "from"
        << file_path;

    QTextStream stream(&scriptFile);
    QString contents = stream.readAll();
    scriptFile.close();
    auto result = engine_->evaluate(contents, file_path);
    if (result.isError()) {
      qCWarning(AnimationRunnerLog)
          << "Loading" << file_path_without_resource << "failed at line"
          << result.property("lineNumber").toInt() << ":" << result.toString();
    }
  }
}

void AnimationRunner::stopScript() {
  engine_->setInterrupted(true);
  do_loop_ = false;
  loop_timer_->stop();
}

void AnimationRunner::runScript(QString animation_script) {
  // reset screen
  screen_interface_js_->setAllPixels(kClearColor);
  screen_->clear();

  // reset runner
  stopScript();
  engine_->setInterrupted(false);
  previous_frame_time_ = QDateTime::currentDateTime();
  animation_obj_ = QJSValue();

  // create new animation runner from script
  auto eval_result = engine_->evaluate("\"use strict\";\n" + animation_script +
                                       "\nnew Animation();");
  if (eval_result.isError()) {
    // this error can be caused by the user, so it's only logged in debug mode
    qCDebug(AnimationRunnerLog)
        << "eval error at line" << eval_result.property("lineNumber").toInt()
        << ":" << eval_result.toString();
  } else if (eval_result.property("update").isCallable()) {
    // everything seems fine, start loop
    animation_obj_ = eval_result;
    do_loop_ = true;
    loop();
  } else {
    qCDebug(AnimationRunnerLog)
        << "Created instance does not have update function:"
        << eval_result.toString();
  }
}

void AnimationRunner::loop() {
  qCDebug(AnimationRunnerLog)
      << "looping on thread:" << QThread::currentThread()
      << "application thread is:" << QCoreApplication::instance()->thread();

  // create context
  auto current_frame_time = QDateTime::currentDateTime();
  auto animation_params = createAnimationContext(
      engine_, previous_frame_time_, current_frame_time, screen_interface_js_);
  previous_frame_time_ = current_frame_time;

  // run animation fucntion
  auto animation_function = animation_obj_.property("update");
  auto result =
      animation_function.callWithInstance(animation_obj_, {animation_params});

  // handle result
  if (result.isDate()) {
    int requested_interval =
        QDateTime::currentDateTime().msecsTo(result.toDateTime());
    int corrected_interval =
        std::max(requested_interval, kMinimumFrameIntervalMS);

    qCDebug(AnimationRunnerLog)
        << "loop sleeping for " << corrected_interval << "ms";
    // start timer for next loop itteration
    if (do_loop_) {
      loop_timer_->start(corrected_interval);
    }
  } else if (result.isUndefined()) {
    qCDebug(AnimationRunnerLog) << "got \"undefined\" loop ending";
    do_loop_ = false;
  } else {
    qCDebug(AnimationRunnerLog)
        << "loop error at line" << result.property("lineNumber").toInt() << ":"
        << result.toString();
    do_loop_ = false;
  }
}

QSize AnimationRunner::getResolution() { return screen_->getResolution(); }
