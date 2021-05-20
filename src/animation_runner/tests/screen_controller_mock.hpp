#pragma once

#include <vector>

#include "gmock/gmock.h"
#include "screen_controller_interface.hpp"

class ScreenControllerMock : public ScreenControllerInterface {
 public:
  MOCK_METHOD(void, draw, (const std::vector<QColor>& pixels), (override));
  MOCK_METHOD(QSize, getResolution, (), (override));
};
