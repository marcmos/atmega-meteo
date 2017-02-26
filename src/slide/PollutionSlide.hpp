#pragma once

#include "Slide2x16.hpp"
#include "../Pollution.hpp"

class PollutionSlide: public Slide2x16 {
public:
  PollutionSlide(const Pollution &pollution);

  bool update();

private:
  const Pollution &pollution;
  char lines[2][16];
};
