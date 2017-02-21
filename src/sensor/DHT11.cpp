#include "DHT11.hpp"

#include "../defines.hpp"
#include "../bitops.hpp"

#include <stddef.h>
#include <avr/io.h>
#include <util/delay.h>

DHT11::DHT11() {
  // Make sure DHT-11 has time to initialize.
  _delay_ms(2000);
}

void DHT11::read() {
  uint8_t data[5] = {0, 0, 0, 0, 0};

  // Set data pin as output.
  SET(DDR, DHT11_PIN);

  // Pull down voltage for at least 18ms.
  CLR(PORT, DHT11_PIN);
  _delay_ms(20);

  // Pull voltage high and wait for response.
  SET(PORT, DHT11_PIN);
  CLR(DDR, DHT11_PIN);

  // FIXME Add macros, remove hardcoded values.
  loop_until_bit_is_clear(PINA, 0);
  loop_until_bit_is_set(PINA, 0);

  for(int i = 0; i < 5; ++i) {
    for(int j = 7; j >= 0; --j) {
      loop_until_bit_is_clear(PINA, 0);
      loop_until_bit_is_set(PINA, 0);
      _delay_us(30);
      data[i] |= bit_is_set(PINA, 0) << j;
    }
  }

  humid = data[0];
  temp = data[2];
}

uint8_t DHT11::get_humid() const {
  return humid;
}

uint8_t DHT11::get_temp() const {
  return temp;
}
