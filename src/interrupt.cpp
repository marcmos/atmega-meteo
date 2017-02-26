#include <avr/interrupt.h>

#include "interrupt.hpp"

namespace interrupt {
  static Handler *serial_handler = NULL;

  void set_serial_handler(Handler *handler) {
    serial_handler = handler;
    sei();
    handler->enable_interrupts();
  }

  ISR(USART0_RX_vect) {
    if(serial_handler) serial_handler->interrupt();
  }
}
