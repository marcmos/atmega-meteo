#include "Serial.hpp"

#include <util/delay.h>

char Serial::read() {
  char c;

  switch(c = uart.rx()) {
  case '\r':
    uart.tx('\r');
    uart.tx('\n');
    break;
  default:
    uart.tx(c);
    break;
  }

  return c;
}
