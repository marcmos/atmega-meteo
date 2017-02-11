#include "dht11.h"

#include "defines.h"
#include "bitops.h"

#include <avr/io.h>
#include <util/delay.h>

void dht11_init() {
  _delay_ms(2000);
}

bool dht11_read(uint8_t *data) {
  int8_t i, j;

  data[0] = data[1] = data[2] = data[3] = data[4] = 0;

  // Set data pin as output
  SET(DDR, DHT11);

  // Pull down voltage for at least 18ms
  CLR(PORT, DHT11);
  _delay_ms(20);

  // Pull voltage high and wait for response
  SET(PORT, DHT11);
  CLR(DDR, DHT11);

  // FIXME Add macros, remove hardcoded values
  loop_until_bit_is_clear(PINA, 0);
  loop_until_bit_is_set(PINA, 0);

  for(i = 0; i < 5; ++i) {
    for(j = 7; j >= 0; --j) {
      loop_until_bit_is_clear(PINA, 0);
      loop_until_bit_is_set(PINA, 0);
      _delay_us(30);
      data[i] |= bit_is_set(PINA, 0) << j;
    }
  }

  // FIXME Add checksum check
  return true;
}
