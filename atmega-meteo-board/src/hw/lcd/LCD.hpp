#pragma once

#include "Slide.hpp"

class LCD {
public:
  virtual void reset() = 0;
  virtual void print(const char *str) = 0;
  virtual bool display(Slide *slide);
};
