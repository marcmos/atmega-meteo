#pragma once

class Pollution {
public:
  unsigned int pm_2_5, pm_10;

  unsigned int pm_2_5_percent() const { return pm_2_5 * 100 / PM_2_5_LIMIT; }
  unsigned int pm_10_percent() const { return pm_10 * 100 / PM_10_LIMIT; }

private:
  static const unsigned int PM_2_5_LIMIT = 25;
  static const unsigned int PM_10_LIMIT = 50;
};
