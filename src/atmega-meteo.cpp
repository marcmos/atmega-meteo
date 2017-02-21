#include "lcd/HD44780.hpp"
#include "lcd/Slide2x16.hpp"
#include "serial/Serial.hpp"

#include <util/delay.h>

int main(void) {
  HD44780 lcd;
  // Serial serial = Serial();
  Slide2x16 slide("line1", "line2");
  Slide2x16 slide2("line3", "line4");

  return 0;
}
