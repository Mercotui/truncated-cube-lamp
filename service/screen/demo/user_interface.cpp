#include "screen/demo/user_interface.hpp"

#include <ncurses.h>

#include <utility>

namespace {
constexpr int kScreenPreviewYOffset = 4;
}  // namespace

UserInterface::UserInterface() {
  initscr();              // initialize ncurses
  cbreak();               // dont wait for terminal flush
  curs_set(0);            // set cursor invsible
  noecho();               // dont echo input
  nodelay(stdscr, TRUE);  // set getch to be non-blocking
  keypad(stdscr, TRUE);   // enable arrow keys
}

UserInterface::~UserInterface() { endwin(); }

UserInterface::Button UserInterface::getButtonPress() {
  switch (wgetch(stdscr)) {
    case '1':
    case 'r':
      return Button::kRed;
    case '2':
    case 'g':
      return Button::kGreen;
    case '3':
    case 'b':
      return Button::kBlue;
    case KEY_UP:
      return Button::kUp;
    case KEY_DOWN:
      return Button::kDown;
    case KEY_LEFT:
      return Button::kLeft;
    case KEY_RIGHT:
      return Button::kRight;
    case 'd':
      return Button::kDraw;
    case 'q':
      return Button::kExit;
    default:
      break;
  }
  return Button::kNop;
}

void UserInterface::draw(const unsigned pixel_value, const int coord_x,
                         const int coord_y, const int res_x, const int res_y) {
  move(0, 0);
  wclear(stdscr);
  attron(A_BOLD);
  printw("SCREEN CONTROLLER TEST\n");
  attroff(A_BOLD);
  printw(" Commands:\t Quit(q) Draw(d) RGB(rgb or 123) Navigate(arrow keys)\n");
  printw(" Resolution:\t%d by %d\n", res_x, res_y);
  printw(" Selected:\t(%d , %d )=%06x\n", coord_x, coord_y, pixel_value);
  printw(" Screen Preview:\n");
  for (int x = 0; x < res_x; ++x) {
    for (int y = 0; y < res_y; ++y) {
      mvprintw(kScreenPreviewYOffset + res_y - y, x, ".");
    }
  }
  mvprintw(kScreenPreviewYOffset + res_y - coord_y, coord_x, "X");
}
