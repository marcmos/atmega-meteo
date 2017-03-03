#pragma once

#include "Slide2x16.hpp"
#include "../hw/sensor/DHT11.hpp"

class IndoorSlide : public Slide2x16 {
public:
  IndoorSlide(DHT11 &dht11);

  bool update();

private:
  DHT11 &dht11;

  char lines[2][16];
};
