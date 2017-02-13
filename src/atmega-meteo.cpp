#include "lcd/HD44780.hpp"

#include <util/delay.h>

int main(void) {
  HD44780 lcd = HD44780();
  const uint16_t period_ms = 100;

  while(true) {
    lcd.display("This is a test\n");
    _delay_ms(period_ms);
    lcd.display("in second line.\n");
    _delay_ms(period_ms);
    lcd.display("HD44780\n");
    _delay_ms(period_ms);
    lcd.display("on duty!\n");
    _delay_ms(period_ms);

    lcd.reset();
  }

  return 0;
}
