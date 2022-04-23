#pragma once

#include <QtCore/QThread>

#include "animation_runner/animation_runner.hpp"

class AnimationThread : public QThread {
  Q_OBJECT

 public:
  explicit AnimationThread(AnimationRunner* runner);
  virtual ~AnimationThread();

 private:
  AnimationRunner* runner_;
};
