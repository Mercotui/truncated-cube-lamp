// dummy thick, that is.
#pragma once

#include <memory>
#include <vector>

#include "screen/screen_controller_interface.hpp"

class DummyScreenController final : public ScreenControllerInterface {
 public:
  DummyScreenController() = default;
  ~DummyScreenController() final = default;

  void draw(const std::vector<QColor>& pixels) final;
  void clear() final;
  QSize getResolution() final;
};
