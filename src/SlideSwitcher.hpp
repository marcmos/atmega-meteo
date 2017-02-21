#pragma once

#include "lcd/LCD.hpp"
#include "lcd/Slide.hpp"

class SlideSwitcher {
public:
  SlideSwitcher(LCD &lcd, Slide **slides, size_t count);

  void next();

private:
  LCD &lcd;
  Slide **slides;
  size_t current, count;
};
