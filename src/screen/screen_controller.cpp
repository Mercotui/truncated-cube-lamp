#include "screen_controller.hpp"

#include <QLoggingCategory>

#include "./ws2811.h"

namespace {
constexpr int kScreenWidth = 8;
constexpr int kScreenHeight = 8;
constexpr int kDmaNumber = 10;
constexpr int kPixelCount = kScreenWidth * kScreenHeight;
constexpr int kGpioPin = 10;  // SPI MOSI
constexpr int kLedStripType = SK6812_STRIP;
constexpr uint8_t kBrightness = 128;  // half brightness is more than blinding

}  // namespace

Q_LOGGING_CATEGORY(ScreenControllerLog, "animation.screen", QtInfoMsg)

ScreenController::ScreenController()
    : led_panel_(std::make_unique<ws2811_t>()) {
  // configure driver
  led_panel_->freq = WS2811_TARGET_FREQ;
  led_panel_->dmanum = kDmaNumber;
  memset(led_panel_->channel, 0, sizeof(ws2811_channel_t) * RPI_PWM_CHANNELS);
  // configure led matrix
  led_panel_->channel[0].count = kPixelCount;
  led_panel_->channel[0].gpionum = kGpioPin;
  led_panel_->channel[0].strip_type = kLedStripType;
  led_panel_->channel[0].brightness = kBrightness;
  led_panel_->channel[0].invert = 0;

  // try to initialize panel
  if (const ws2811_return_t status = ws2811_init(led_panel_.get());
      status != WS2811_SUCCESS) {
    led_panel_.reset();
    qCWarning(ScreenControllerLog)
        << "Driver init:" << ws2811_get_return_t_str(status);
  }
}

ScreenController::~ScreenController() { ws2811_fini(led_panel_.get()); }

void ScreenController::draw(const std::vector<QColor>& pixels) {
  if (!led_panel_) {
    Q_ASSERT_X(false, Q_FUNC_INFO, "Screen not initialized");
    return;
  }

  if (const ws2811_return_t status = ws2811_wait(led_panel_.get());
      status != WS2811_SUCCESS) {
    qCWarning(ScreenControllerLog)
        << "Driver wait:" << ws2811_get_return_t_str(status);
  }

  for (int idx = pixels.size() - 1; idx >= 0; --idx) {
    led_panel_->channel[0].leds[idx] = pixels[idx].rgb();
  }

  if (const ws2811_return_t status = ws2811_render(led_panel_.get());
      status != WS2811_SUCCESS) {
    qCWarning(ScreenControllerLog)
        << "Driver render:" << ws2811_get_return_t_str(status);
  }
}

QSize ScreenController::getResolution() {
  return {kScreenWidth, kScreenHeight};
}
