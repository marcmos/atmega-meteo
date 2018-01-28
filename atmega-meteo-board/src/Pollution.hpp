#pragma once

#include <stdint.h>

class Pollution {
public:
  Pollution():
    _initialized(false)
  {}

  bool initialized() const { return _initialized; }

  uint16_t pm_2_5() const { return _pm_2_5; }
  uint16_t pm_10() const { return _pm_10; }

  uint16_t pm_2_5_percent() const { return _pm_2_5 * 100 / PM_2_5_LIMIT; }
  uint16_t pm_10_percent() const { return _pm_10 * 100 / PM_10_LIMIT; }

  void set(uint16_t pm_2_5, uint16_t pm_10) {
    _pm_2_5 = pm_2_5;
    _pm_10 = pm_10;
    _initialized = true;
  }

private:
  bool _initialized;
  uint16_t _pm_2_5, _pm_10;

  static const uint16_t PM_2_5_LIMIT = 25;
  static const uint16_t PM_10_LIMIT = 50;
};
