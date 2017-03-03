#pragma once

#include <stdint.h>

class DHT11 {
public:
  DHT11(bool fast = true);

  void read();

  uint8_t humid() const;
  uint8_t temp() const;

private:
  uint8_t _humid;
  uint8_t _temp;
};
