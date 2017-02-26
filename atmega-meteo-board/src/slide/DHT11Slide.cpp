#include "DHT11Slide.hpp"

#include <stdio.h>

DHT11Slide::DHT11Slide(DHT11 &dht11) :
  Slide2x16(lines[0], lines[1]),
  dht11(dht11)
{}

bool DHT11Slide::update() {
  dht11.read();

  snprintf(lines[0], 16, "Temp: %d\xdf" "C", dht11.get_temp());
  snprintf(lines[1], 16, "Humid: %d%%", dht11.get_humid());

  return true;
}
