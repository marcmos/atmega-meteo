#pragma once

#include "hw/interrupt.hpp"
#include "hw/serial/UART.hpp"
#include "Pollution.hpp"
#include "Weather.hpp"

class SerialHandler: public interrupt::Handler {
public:
  SerialHandler(UART &uart, Pollution *pollution, Weather *weather);

  void enable_interrupts();
  void interrupt();

private:
  UART &uart;
  Pollution *pollution;
  Weather *weather;

  enum Opcode {
    OP_POLLUTION = 0x20,
    OP_WEATHER = 0x21,
  };
};
