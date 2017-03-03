#include <avr/io.h>

#include "SerialHandler.hpp"

SerialHandler::SerialHandler(UART &uart, Pollution *pollution, Weather *weather) :
  uart(uart),
  pollution(pollution),
  weather(weather)
{}

void SerialHandler::enable_interrupts() {
  uart.enable_interrupts();
}

void SerialHandler::interrupt() {
  char bytes[2];

  switch(uart.rx()) {
  case SerialHandler::OP_POLLUTION:
    if(!pollution) break;
    bytes[0] = uart.rx();
    bytes[1] = uart.rx();
    pollution->set(bytes[0], bytes[1]);
    break;
  case SerialHandler::OP_WEATHER:
    if(!weather) break;
    bytes[0] = uart.rx();
    bytes[1] = uart.rx();
    weather->set(bytes[0], bytes[1]);
    break;
  default:
    break;
  }
}
