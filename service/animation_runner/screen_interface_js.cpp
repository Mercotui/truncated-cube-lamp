#include "animation_runner/screen_interface_js.hpp"

#include <QColor>
#include <QLoggingCategory>
#include <QObject>
#include <QSize>
#include <vector>

Q_LOGGING_CATEGORY(ScreenInterfaceLog, "animation.screeninterface", QtInfoMsg)

ScreenInterfaceJs::ScreenInterfaceJs(QSize resolution, QObject* parent)
    : pixels_(resolution.width() * resolution.width(), "black"),
      resolution_(resolution),
      QObject(parent) {}

const std::vector<QColor>& ScreenInterfaceJs::pixels() { return pixels_; }

void ScreenInterfaceJs::setPixel(const int x, const int y, QColor color) {
  pixels_[wrapCoordinates(x, y)] = color;
}

QColor ScreenInterfaceJs::getPixel(const int x, const int y) {
  return pixels_[wrapCoordinates(x, y)];
}

void ScreenInterfaceJs::setAllPixels(QColor color) {
  std::fill(pixels_.begin(), pixels_.end(), color);
}

int ScreenInterfaceJs::wrapCoordinates(const int x, const int y) {
  auto clamped_x = std::clamp(x, 0, resolution_.width() - 1);
  auto clamped_y = std::clamp(y, 0, resolution_.height() - 1);
  return (clamped_y * resolution_.width()) + clamped_x;
}
