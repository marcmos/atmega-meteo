#pragma once

#include "Slide2x16.hpp"
#include "../Weather.hpp"

class WeatherSlide: public Slide2x16 {
public:
  WeatherSlide(const Weather &weather);

  bool update();

private:
  const Weather &weather;
  char lines[2][17];
};
