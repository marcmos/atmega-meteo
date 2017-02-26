#include "UART.hpp"

#include <avr/io.h>

#include "../defines.hpp"

UART::UART() {
  UBRR0L = (F_CPU / (16UL * UART_BAUD)) - 1;
  UCSR0B = _BV(TXEN0) | _BV(RXEN0); /* tx/rx enable */
}

void UART::tx(uint8_t b) {
  loop_until_bit_is_set(UCSR0A, UDRE0);
  UDR0 = b;
}

uint8_t UART::rx() {
  loop_until_bit_is_set(UCSR0A, RXC0);
  return UDR0;
}

void UART::enable_interrupts() {
  UCSR0B |= _BV(RXCIE0);
}
