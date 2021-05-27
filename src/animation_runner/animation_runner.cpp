#include "animation_runner.hpp"

#include <QCoreApplication>
#include <QLoggingCategory>
#include <QThread>
#include <algorithm>
#include <utility>

Q_LOGGING_CATEGORY(AnimationRunnerLog, "animation.runner", QtDebugMsg)

namespace {
constexpr int kMinimumFrameIntervalMS = 16;  // for max 60 fps
}  // namespace

AnimationRunner::AnimationRunner(
    std::unique_ptr<ScreenControllerInterface> screen_controller)
    : engine_(),
      screen_interface_js_(screen_controller->getResolution()),
      screen_(std::move(screen_controller)) {
  this->moveToThread(this);
  engine_.moveToThread(this);
  screen_interface_js_.moveToThread(this);
  engine_.installExtensions(QJSEngine::ConsoleExtension);
  engine_.globalObject().setProperty("screen",
                                     engine_.newQObject(&screen_interface_js_));

  connect(&screen_interface_js_, &ScreenInterfaceJs::draw,
          [this]() { screen_->draw(screen_interface_js_.pixels()); });
}

void AnimationRunner::runScript(QString animation_script) {
  previous_frame_time_ = QDateTime::currentDateTime();
  auto result = engine_.evaluate(animation_script);
  if (result.isCallable()) {
    loop(result);
  } else {
    qCDebug(AnimationRunnerLog) << "eval result" << result.toString();
  }
}

void AnimationRunner::loop(QJSValue animation_function) {
  qCDebug(AnimationRunnerLog)
      << "looping on thread:" << QThread::currentThread()
      << "application thread is:" << QCoreApplication::instance()->thread();

  bool do_loop = true;
  while (do_loop) {
    auto animation_params = engine_.newObject();
    auto current_frame_time = QDateTime::currentDateTime();
    animation_params.setProperty("current_frame_time",
                                 engine_.toScriptValue(current_frame_time));
    animation_params.setProperty("previous_frame_time",
                                 engine_.toScriptValue(previous_frame_time_));
    previous_frame_time_ = current_frame_time;

    auto result = animation_function.call({animation_params});
    if (result.isDate()) {
      int requested_interval =
          QDateTime::currentDateTime().msecsTo(result.toDateTime());
      qCDebug(AnimationRunnerLog)
          << "sleeping for ms" << requested_interval << "ms";
      QThread::msleep(std::max(requested_interval, kMinimumFrameIntervalMS));
    } else {
      qCDebug(AnimationRunnerLog) << "eval result" << result.toString();
      do_loop = false;
    }
  }
}

QSize AnimationRunner::getResolution() { return screen_->getResolution(); }
