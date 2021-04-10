#pragma once

#include <memory>

#include "screen_controller_interface.hpp"

struct ws2811_t;

class ScreenController final : public ScreenControllerInterface {
 public:
  ScreenController();
  virtual ~ScreenController() final;

  void draw(const std::vector<QColor>& pixels) final;
  QSize getResolution() final;

 private:
  std::unique_ptr<ws2811_t> led_panel_;
};
