#pragma once

#include <QJSEngine>
#include <memory>

#include "screen_controller_interface.hpp"

class AnimationRunner : public QObject {
  Q_OBJECT
 public:
  AnimationRunner(std::unique_ptr<ScreenControllerInterface> screen_controller);

  void run(QString animation_script);

 private:
  QJSEngine engine_;
  std::unique_ptr<ScreenControllerInterface> screen_;
};
