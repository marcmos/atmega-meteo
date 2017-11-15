#include "IndoorSlide.hpp"

#include <stdio.h>

IndoorSlide::IndoorSlide(DHT11 &dht11) :
  Slide2x16(lines[0], lines[1]),
  dht11(dht11),
  lines {"Indoor", "Unknown"}
{}

bool IndoorSlide::update() {
  dht11.read();
  snprintf(lines[1], 17, "T: %hhu\xdf" "C, H: %hhu%%", dht11.temp(), dht11.humid());
  return true;
}
