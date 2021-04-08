#pragma once

#include "screen_controller_interface.hpp"

class ScreenController final : public ScreenControllerInterface {
 public:
  virtual ~ScreenController() final = default;

  void draw(const std::vector<QColor>& pixels) final;
  QSize getResolution() final;
};
