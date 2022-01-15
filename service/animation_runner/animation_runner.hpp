#pragma once

#include <QtCore/QDateTime>
#include <QtCore/QObject>
#include <QtCore/QSize>
#include <QtCore/QTimer>
#include <QtQml/QJSEngine>
#include <atomic>
#include <memory>

#include "screen_controller_interface.hpp"
#include "screen_interface_js.hpp"

class AnimationRunner : public QObject {
  Q_OBJECT

 public:
  explicit AnimationRunner(
      std::unique_ptr<ScreenControllerInterface> screen_controller);

  virtual ~AnimationRunner();

  void runScript(QString animation_script);
  void stopScript();
  QSize getResolution();

 private:
  void loop();
  void loadLibraries();

  std::atomic<bool> do_loop_;
  QTimer* loop_timer_;
  QJSEngine* engine_;
  ScreenInterfaceJs* screen_interface_js_;
  std::unique_ptr<ScreenControllerInterface> screen_;
  QJSValue animation_obj_;
  QDateTime previous_frame_time_;
};