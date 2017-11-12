#pragma once

class Weather {
public:
  Weather():
    _initialized(false)
  {};

  bool initialized() const { return _initialized; }

  unsigned int temp() const { return _temp; }
  unsigned int humid() const { return _humid; }
  unsigned int hour() const { return _hour; }
  unsigned int minute() const { return _minute; }

  void set(unsigned int temp, unsigned int humid, unsigned int hour, unsigned int minute) {
    _temp = temp;
    _humid = humid;
    _hour = hour;
    _minute = minute;
    _initialized = true;
  }

private:
  bool _initialized;
  unsigned int _temp, _humid, _hour, _minute;
};
