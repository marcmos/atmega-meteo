#pragma once

#include "UART.hpp"

class Serial {
public:
  char read();

private:
  UART uart;
};
