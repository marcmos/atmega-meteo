#pragma once

#include <stdint.h>

class UART {
public:
  UART();

public:
  void tx(uint8_t b);
  uint8_t rx();

  void enable_interrupts();
};
