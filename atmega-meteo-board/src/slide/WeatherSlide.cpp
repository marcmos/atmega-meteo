#include "WeatherSlide.hpp"

#include <stdio.h>

WeatherSlide::WeatherSlide(const Weather &weather) :
  Slide2x16(lines[0], lines[1]),
  weather(weather),
  lines {"Weather", "Unknown"}
{}

bool WeatherSlide::update() {
  if(!weather.initialized())
    return false;

  snprintf(lines[0], 17, "Weather %02hhu:%02hhu", weather.hour(), weather.minute());
  snprintf(lines[1], 17, "T: %hhd\xdf" "C, H: %hhu%%", weather.temp(), weather.humid());

  return true;
}
