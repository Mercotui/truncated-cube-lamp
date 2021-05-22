#pragma once

class UserInterface {
 public:
  enum class Button {
    kRed = 0,
    kGreen,
    kBlue,
    kUp,
    kDown,
    kLeft,
    kRight,
    kDraw,
    kExit,
    kNop
  };

  UserInterface();
  ~UserInterface();

  Button getButtonPress();
  void draw(const unsigned pixel_value, const int coord_x, const int coord_y,
            const int res_x, const int res_y);
};
