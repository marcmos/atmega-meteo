#include <util/delay.h>
#include <avr/io.h>
#include <avr/sfr_defs.h>

int main(void) {
  DDRB |= _BV(DDB7);
  while(1) {
    PORTB ^= _BV(PB7);
    _delay_ms(5000L);
  }

  return 0;
}
