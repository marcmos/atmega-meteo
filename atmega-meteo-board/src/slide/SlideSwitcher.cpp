#include "SlideSwitcher.hpp"

SlideSwitcher::SlideSwitcher(LCD &lcd, Slide **slides, size_t count) :
  lcd(lcd),
  slides(slides),
  current(0),
  count(count)
{}

void SlideSwitcher::next() {
  bool updated = false;

  do {
    updated = lcd.display(slides[current++ % count]);
  } while(!updated);
}
