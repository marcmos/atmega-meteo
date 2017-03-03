#pragma once

class Weather {
public:
  Weather():
    _initialized(false)
  {};

  bool initialized() const { return _initialized; }

  unsigned int temp() const { return _temp; }
  unsigned int humid() const { return _humid; }

  void set(unsigned int temp, unsigned int humid) {
    _temp = temp;
    _humid = humid;
    _initialized = true;
  }

private:
  bool _initialized;
  unsigned int _temp, _humid;
};
