#include "screen/dummy_screen_controller.hpp"

#include <QLoggingCategory>

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

void DummyScreenController::clear() {
  qCInfo(DummyScreenControllerLog) << "Clear";
}

QSize DummyScreenController::getResolution() {
  return {kScreenWidth, kScreenHeight};
}
