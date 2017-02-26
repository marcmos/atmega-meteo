#pragma once

#include "serial/Serial.hpp"

namespace interrupt {
  class Handler {
  public:
    virtual void enable_interrupts() = 0;
    virtual void interrupt() = 0;
  };

  void set_serial_handler(Handler *handler);
}
