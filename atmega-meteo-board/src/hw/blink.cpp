#include "blink.hpp"

#include "defines.hpp"
#include "bitops.hpp"

#include <avr/io.h>
#include <util/delay.h>

void blink_init() {
  SET(DDR, LED);
}

void blink() {
  TOGGLE(PORT, LED);
}

void blink_loop() {
  while(1) {
    blink();
    _delay_ms(1000L);
  }
}
