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

  snprintf(lines[0], 16, "Weather %02u:%02u", weather.hour(), weather.minute());
  snprintf(lines[1], 16, "T: %d\xdf" "C, H: %u%%", weather.temp(), weather.humid());

  return true;
}
