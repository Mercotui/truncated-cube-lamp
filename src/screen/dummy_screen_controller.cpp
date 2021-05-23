#include "dummy_screen_controller.hpp"

#include <QLoggingCategory>

#include "./ws2811.h"

namespace {
constexpr int kScreenWidth = 8;
constexpr int kScreenHeight = 8;
constexpr int kPixelCount = kScreenWidth * kScreenHeight;

}  // namespace

Q_LOGGING_CATEGORY(DummyScreenControllerLog, "screen.dummy", QtWarningMsg)

void DummyScreenController::draw(const std::vector<QColor>& pixels) {
  qCInfo(DummyScreenControllerLog) << "Draw";
  qCDebug(DummyScreenControllerLog) << pixels;
}

QSize DummyScreenController::getResolution() {
  return {kScreenWidth, kScreenHeight};
}
