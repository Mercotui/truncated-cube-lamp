#include "animation_runner.hpp"

#include <utility>

AnimationRunner::AnimationRunner(
    std::unique_ptr<ScreenControllerInterface> screen_controller)
    : screen_(std::move(screen_controller)) {
  engine_.installExtensions(QJSEngine::ConsoleExtension);
}

void AnimationRunner::run(QString animation_script) {
  engine_.evaluate(animation_script);
  screen_->draw({{"green"}});
}

QSize AnimationRunner::getResolution() { return screen_->getResolution(); }
