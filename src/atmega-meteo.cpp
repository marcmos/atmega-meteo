#include "lcd/HD44780.hpp"
#include "sensor/DHT11.hpp"
#include "DHT11Slide.hpp"
#include "SlideSwitcher.hpp"

#include <util/delay.h>

int main(void) {
  HD44780 lcd;
  DHT11 dht11;
  DHT11Slide dht11_slide(dht11);
  Slide2x16 test_slide("NOBODY EXPECTS", "THE");
  Slide2x16 test_slide2("SPANINSH", "INQUISITION");
  Slide *slides[] = {&dht11_slide, &test_slide, &test_slide2};
  SlideSwitcher switcher(lcd, slides, 3);

  while(1) {
    switcher.next();
    _delay_ms(5000);
  }

  return 0;
}
