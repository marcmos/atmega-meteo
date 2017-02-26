#pragma once

#include "hw/interrupt.hpp"
#include "hw/serial/UART.hpp"
#include "Pollution.hpp"

class SerialHandler: public interrupt::Handler {
public:
  SerialHandler(UART &uart, Pollution *pollution);

  void enable_interrupts();
  void interrupt();

private:
  UART &uart;
  Pollution *pollution;
};
