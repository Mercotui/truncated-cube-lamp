#include <QtCore/QThread>
#include <QtCore/QtCore>

#include "screen/demo/user_interface.hpp"
#include "screen/screen_controller.hpp"

using Button = UserInterface::Button;

namespace {
void changeCoordinates(const Button button, QPoint* coordinates,
                       const QSize& resolution) {
  switch (button) {
    case Button::kUp: {
      coordinates->setY(
          std::clamp(coordinates->y() + 1, 0, resolution.height() - 1));
      break;
    }
    case Button::kDown: {
      coordinates->setY(
          std::clamp(coordinates->y() - 1, 0, resolution.height() - 1));
      break;
    }
    case Button::kLeft: {
      coordinates->setX(
          std::clamp(coordinates->x() - 1, 0, resolution.width() - 1));
      break;
    }
    case Button::kRight: {
      coordinates->setX(
          std::clamp(coordinates->x() + 1, 0, resolution.width() - 1));
      break;
    }
    default: {
      break;
    }
  }
}

void pixelChangeColor(const Button button, std::vector<QColor>* pixels,
                      const QPoint& coordinates, const QSize& resolution) {
  const int index = (coordinates.y() * resolution.width()) + coordinates.x();
  auto& pixel = (*pixels)[index];
  switch (button) {
    case Button::kRed: {
      if (pixel.red()) {
        pixel.setRed(0);
      } else {
        pixel.setRed(255);
      }
      break;
    }
    case Button::kGreen: {
      if (pixel.green()) {
        pixel.setGreen(0);
      } else {
        pixel.setGreen(255);
      }
      break;
    }
    case Button::kBlue: {
      if (pixel.blue()) {
        pixel.setBlue(0);
      } else {
        pixel.setBlue(255);
      }
      break;
    }
    default: {
      break;
    }
  }
}
}  // namespace

int main(int argc, char** argv) {
  UserInterface user_interface;
  bool app_running = true;
  bool ui_dirty = true;

  ScreenController led_screen;
  QSize resolution = led_screen.getResolution();
  QPoint coordinates = {0, 0};
  std::vector<QColor> pixels(resolution.width() * resolution.height());

  while (app_running) {
    if (ui_dirty) {
      const int pixel_value =
          pixels[(coordinates.y() * resolution.width()) + coordinates.x()]
              .rgb();
      user_interface.draw(pixel_value, coordinates.x(), coordinates.y(),
                          resolution.width(), resolution.height());
      ui_dirty = false;
    }

    Button button = user_interface.getButtonPress();
    switch (button) {
      case Button::kRed:
      case Button::kGreen:
      case Button::kBlue: {
        pixelChangeColor(button, &pixels, coordinates, resolution);
        ui_dirty = true;
        break;
      }
      case Button::kUp:
      case Button::kDown:
      case Button::kLeft:
      case Button::kRight: {
        changeCoordinates(button, &coordinates, resolution);
        ui_dirty = true;
        break;
      }
      case Button::kDraw: {
        led_screen.draw(pixels);
        break;
      }
      case Button::kExit: {
        app_running = false;
        break;
      }
      default: {
        QThread::usleep(20);
        break;
      }
    }
  }

  return 0;
}
