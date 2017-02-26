#pragma once

#include <stdint.h>

class DHT11 {
public:
  DHT11();

  void read();

  uint8_t get_humid() const;
  uint8_t get_temp() const;

private:
  uint8_t humid;
  uint8_t temp;
};
