#include "lcd/HD44780.hpp"
#include "sensor/DHT11.hpp"
#include "DHT11Slide.hpp"

#include <util/delay.h>

int main(void) {
  HD44780 lcd;
  DHT11 dht11;
  DHT11Slide dht11_slide(dht11);

  while(1) {
    lcd.display(&dht11_slide);
    _delay_ms(1000);
  }

  return 0;
}
