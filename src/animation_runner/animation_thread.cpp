#include "animation_thread.hpp"

#include <QtCore/QLoggingCategory>

Q_LOGGING_CATEGORY(AnimationThreadLog, "animation.thread", QtInfoMsg)

namespace {
constexpr unsigned kWaitTimeMS = 1000;
}  // namespace

AnimationThread::AnimationThread(AnimationRunner* runner)
    : QThread(), runner(runner) {
  start();

  runner->moveToThread(this);
}

AnimationThread::~AnimationThread() {
  runner->stopScript();
  quit();

  while (!wait(kWaitTimeMS)) {
    qCInfo(AnimationThreadLog)
        << "Still waiting for animation thread to finish";
  }
}
