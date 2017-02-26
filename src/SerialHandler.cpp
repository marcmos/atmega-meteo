#include <avr/io.h>

#include "SerialHandler.hpp"
#include "serial/UART.hpp"
#include "lcd/HD44780.hpp"

SerialHandler::SerialHandler(UART &uart, Pollution *pollution) :
  uart(uart),
  pollution(pollution)
{}

void SerialHandler::enable_interrupts() {
  uart.enable_interrupts();
}

void SerialHandler::interrupt() {
  switch(uart.rx()) {
  case 32:
    if(!pollution) break;
    pollution->pm_2_5 = uart.rx();
    pollution->pm_10 = uart.rx();
    break;
  default:
    break;
  }
}
