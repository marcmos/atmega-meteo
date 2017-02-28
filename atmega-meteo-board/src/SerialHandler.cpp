#include <avr/io.h>

#include "SerialHandler.hpp"
#include "hw/lcd/HD44780.hpp"

SerialHandler::SerialHandler(UART &uart, Pollution *pollution) :
  uart(uart),
  pollution(pollution)
{}

void SerialHandler::enable_interrupts() {
  uart.enable_interrupts();
}

void SerialHandler::interrupt() {
  switch(uart.rx()) {
  case SerialHandler::OP_POLLUTION:
    if(!pollution) break;
    pollution->set(uart.rx(), uart.rx());
    break;
  default:
    break;
  }
}
