#pragma once

class Pollution {
public:
  Pollution():
    _initialized(false)
  {}

  bool initialized() const { return _initialized; }

  unsigned char pm_2_5() const { return _pm_2_5; }
  unsigned char pm_10() const { return _pm_10; }

  unsigned char pm_2_5_percent() const { return _pm_2_5 * 100 / PM_2_5_LIMIT; }
  unsigned char pm_10_percent() const { return _pm_10 * 100 / PM_10_LIMIT; }

  void set(unsigned char pm_2_5, unsigned char pm_10) {
    _pm_2_5 = pm_2_5;
    _pm_10 = pm_10;
    _initialized = true;
  }

private:
  bool _initialized;
  unsigned char _pm_2_5, _pm_10;

  static const unsigned char PM_2_5_LIMIT = 25;
  static const unsigned char PM_10_LIMIT = 50;
};
