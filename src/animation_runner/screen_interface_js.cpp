#include "screen_interface_js.hpp"

#include <QColor>
#include <QDebug>
#include <QObject>
#include <QSize>
#include <vector>

ScreenInterfaceJs::ScreenInterfaceJs(QSize resolution, QObject* parent)
    : pixels_(resolution.width() * resolution.width(), "black"),
      test_(resolution.width() * resolution.width(), 12),
      resolution_(resolution),
      QObject(parent) {}

const std::vector<QColor>& ScreenInterfaceJs::pixels() { return pixels_; }

void ScreenInterfaceJs::setPixel(const int x, const int y, QColor color) {
  pixels_[wrapCoordinates(x, y)] = color;
}

QColor ScreenInterfaceJs::getPixel(const int x, const int y) {
  return pixels_[wrapCoordinates(x, y)];
}

int ScreenInterfaceJs::wrapCoordinates(const int x, const int y) {
  auto clamped_x = std::clamp(x, 0, resolution_.width() - 1);
  auto clamped_y = std::clamp(y, 0, resolution_.height() - 1);
  return (clamped_y * resolution_.width()) + clamped_x;
}
