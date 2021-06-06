#pragma once

#include <QDateTime>
#include <QJSEngine>
#include <QSize>
#include <QThread>
#include <memory>

#include "screen_controller_interface.hpp"
#include "screen_interface_js.hpp"

class AnimationRunner : public QThread {
  Q_OBJECT
 public:
  explicit AnimationRunner(
      std::unique_ptr<ScreenControllerInterface> screen_controller);

  virtual ~AnimationRunner();

  void runScript(QString animation_script);
  QSize getResolution();

 private:
  void loop(QJSValue animation_function);
  void loadLibraries();

  QJSEngine engine_;
  ScreenInterfaceJs screen_interface_js_;
  std::unique_ptr<ScreenControllerInterface> screen_;
  QDateTime previous_frame_time_;
};
