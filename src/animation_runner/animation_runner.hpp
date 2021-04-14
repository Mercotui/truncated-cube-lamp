#pragma once

#include <QJSEngine>
#include <QSize>
#include <memory>

#include "screen_controller_interface.hpp"
#include "screen_interface_js.hpp"

class AnimationRunner : public QObject {
  Q_OBJECT
 public:
  explicit AnimationRunner(
      std::unique_ptr<ScreenControllerInterface> screen_controller);

  void run(QString animation_script);
  QSize getResolution();

 private:
  QJSEngine engine_;
  ScreenInterfaceJs screen_interface_js_;
  std::unique_ptr<ScreenControllerInterface> screen_;
};
