#include "lcd/HD44780.hpp"
#include "serial/Serial.hpp"

#include <util/delay.h>

int main(void) {
  HD44780 lcd = HD44780();
  Serial serial = Serial();

  const uint16_t period_ms = 1000;

  char buf[2] = {0, 0};

  while(true) {
    // lcd.display("This is a test\n");
    // _delay_ms(period_ms);
    // lcd.display("in second line.\n");
    // _delay_ms(period_ms);
    // lcd.display("HD44780\n");
    // _delay_ms(period_ms);
    // lcd.display("on duty!\n");
    // _delay_ms(period_ms);

    buf[0] = serial.read();
    lcd.display(buf);
    lcd.reset();
  }

  return 0;
}
