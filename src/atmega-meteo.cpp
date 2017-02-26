#include <util/delay.h>

#include "hw/serial/UART.hpp"
#include "hw/lcd/HD44780.hpp"
#include "hw/sensor/DHT11.hpp"
#include "hw/interrupt.hpp"

#include "slide/DHT11Slide.hpp"
#include "slide/SlideSwitcher.hpp"
#include "slide/PollutionSlide.hpp"

#include "SerialHandler.hpp"

int main(void) {
  UART serial;
  HD44780 lcd;

  DHT11 dht11;
  DHT11Slide dht11_slide(dht11);

  Pollution pollution;
  PollutionSlide pollution_slide(pollution);

  Slide *slides[] = {&dht11_slide, &pollution_slide};

  SlideSwitcher switcher(lcd, slides, sizeof(slides) / sizeof(slides[0]));

  SerialHandler serial_handler(serial, &pollution);
  interrupt::set_serial_handler(&serial_handler);

  while(1) {
    switcher.next();
    _delay_ms(2000);
  }

  return 0;
}
