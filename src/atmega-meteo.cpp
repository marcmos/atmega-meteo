#include "lcd/HD44780.hpp"
#include "lcd/Slide2x16.hpp"
#include "serial/Serial.hpp"
#include "sensor/DHT11.hpp"

#include <util/delay.h>

int main(void) {
  HD44780 lcd;
  DHT11 dht11;

  char lines[2][16];
  Slide2x16 slide(lines[0], lines[1]);

  while(1) {
    dht11.read();
    snprintf(lines[0], 16, "Temp: %d\xdf" "C", dht11.get_temp());
    snprintf(lines[1], 16, "Wilg: %d%%", dht11.get_humid());

    lcd.display(&slide);

    _delay_ms(1000);
  }

  return 0;
}
