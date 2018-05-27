#include "PollutionSlide.hpp"

#include <stdio.h>
#include <inttypes.h>

PollutionSlide::PollutionSlide(const Pollution &pollution):
  Slide2x16(lines[0], lines[1]),
  pollution(pollution)
{}

bool PollutionSlide::update() {
  if(!pollution.initialized())
    return false;

  snprintf(lines[0], 17, "2.5: %" PRIu16 " (%" PRIu16 "%%)", pollution.pm_2_5(),
           pollution.pm_2_5_percent());
  snprintf(lines[1], 17, "10: %" PRIu16 " (%" PRIu16 "%%)", pollution.pm_10(),
           pollution.pm_10_percent());

  return true;
}
