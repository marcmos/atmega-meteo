#include <util/delay.h>

#include "hw/serial/UART.hpp"
#include "hw/lcd/HD44780.hpp"
#include "hw/sensor/DHT11.hpp"
#include "hw/interrupt.hpp"
#include "hw/blink.hpp"

#include "slide/IndoorSlide.hpp"
#include "slide/PollutionSlide.hpp"
#include "slide/WeatherSlide.hpp"
#include "slide/SlideSwitcher.hpp"

#include "SerialHandler.hpp"

int main(void) {
  UART serial;
  HD44780 lcd;

  DHT11 dht11;
  IndoorSlide indoor_slide(dht11);

  Pollution pollution;
  PollutionSlide pollution_slide(pollution);

  Weather weather;
  WeatherSlide weather_slide(weather);

  Slide *slides[] = {&indoor_slide, &pollution_slide, &weather_slide};

  SlideSwitcher switcher(lcd, slides, sizeof(slides) / sizeof(slides[0]));

  SerialHandler serial_handler(serial, &pollution, &weather);
  interrupt::set_serial_handler(&serial_handler);

  blink_init();

  while(1) {
    switcher.next();
    _delay_ms(2000);

    if (weather.initialized() && dht11.temp() > weather.temp()) {
      blink();
    }
  }

  return 0;
}
