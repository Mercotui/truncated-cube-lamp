#include "screen_controller.hpp"

#include <QDebug>

namespace {
constexpr int kScreenWidth = 8;
constexpr int kScreenHeight = 8;
constexpr int kPixelCount = kScreenWidth * kScreenHeight;
}  // namespace

void ScreenController::draw(const std::vector<QColor>& pixels) {
  for (const auto& pixel : pixels) {
    qDebug() << pixel;
  }
}

QSize ScreenController::getResolution() {
  return {kScreenWidth, kScreenHeight};
}
