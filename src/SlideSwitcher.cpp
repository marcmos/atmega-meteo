#include "SlideSwitcher.hpp"

SlideSwitcher::SlideSwitcher(LCD &lcd, Slide **slides, size_t count) :
  lcd(lcd),
  slides(slides),
  current(0),
  count(count)
{}

void SlideSwitcher::next() {
  lcd.display(slides[current++ % count]);
}
