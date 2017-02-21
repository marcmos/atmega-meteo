#pragma once

#include "lcd/Slide2x16.hpp"
#include "sensor/DHT11.hpp"

class DHT11Slide : public Slide2x16 {
public:
  DHT11Slide(DHT11 &dht11);

  bool update();

private:
  DHT11 &dht11;

  char lines[2][16];
};
