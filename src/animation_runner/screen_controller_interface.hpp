#pragma once

#include <QColor>
#include <QSize>
#include <vector>

class ScreenControllerInterface {
 public:
  virtual ~ScreenControllerInterface() = default;

  virtual void draw(const std::vector<QColor>& pixels) = 0;
  virtual QSize getResolution() = 0;
};
