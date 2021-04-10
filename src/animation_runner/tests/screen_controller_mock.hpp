#pragma once

#include <vector>

#include "../screen_controller_interface.hpp"
#include "gmock/gmock.h"

class ScreenControllerMock : public ScreenControllerInterface {
 public:
  MOCK_METHOD(void, draw, (const std::vector<QColor>& pixels), (override));
  MOCK_METHOD(QSize, getResolution, (), (override));
};
