#include "animation_runner/animation_thread.hpp"

#include <QtCore/QLoggingCategory>

Q_LOGGING_CATEGORY(AnimationThreadLog, "animation.thread", QtInfoMsg)

namespace {
constexpr unsigned kWaitTimeMS = 500;
constexpr unsigned kTotalAllowedWaitTimeMS = 2000;
}  // namespace

AnimationThread::AnimationThread(AnimationRunner* runner)
    : QThread(), runner_(runner) {
  start();

  runner_->moveToThread(this);
}

AnimationThread::~AnimationThread() {
  unsigned total_wait_time = 0;
  while (!QThread::wait(kWaitTimeMS)) {
    total_wait_time += kWaitTimeMS;

    if (runner_->isLooping()) {
      qCInfo(AnimationThreadLog) << "Waiting for animation to finish";
    } else {
      qCInfo(AnimationThreadLog) << "Waiting for animation thread to finish";
    }
    if (!runner_->isLooping() || total_wait_time > kTotalAllowedWaitTimeMS) {
      qCInfo(AnimationThreadLog) << "Quiting animation thread";
      QThread::quit();
    }
  }
}
