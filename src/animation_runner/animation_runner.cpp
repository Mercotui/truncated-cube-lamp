#include "animation_runner.hpp"

#include <utility>

AnimationRunner::AnimationRunner(
    std::unique_ptr<ScreenControllerInterface> screen_controller)
    : screen_(std::move(screen_controller)),
      screen_interface_js_(screen_controller->getResolution()) {
  engine_.installExtensions(QJSEngine::ConsoleExtension);
  engine_.globalObject().setProperty("screen",
                                     engine_.newQObject(&screen_interface_js_));

  connect(&screen_interface_js_, &ScreenInterfaceJs::draw,
          [this]() { screen_->draw(screen_interface_js_.pixels()); });
}

void AnimationRunner::run(QString animation_script) {
  auto result = engine_.evaluate(animation_script);
  if (result.isError()) {
    qDebug() << "eval result" << result.toString();
  }
}

QSize AnimationRunner::getResolution() { return screen_->getResolution(); }
