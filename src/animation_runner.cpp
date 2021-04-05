#include "animation_runner.hpp"

AnimationRunner::AnimationRunner() {
  engine_.installExtensions(QJSEngine::ConsoleExtension);
}

void AnimationRunner::run(QString animation_script) {
  engine_.evaluate(animation_script);
}
