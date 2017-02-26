#pragma once

#include "../hw/lcd/LCD.hpp"
#include "../hw/lcd/Slide.hpp"

class SlideSwitcher {
public:
  SlideSwitcher(LCD &lcd, Slide **slides, size_t count);

  void next();

private:
  LCD &lcd;
  Slide **slides;
  size_t current, count;
};
