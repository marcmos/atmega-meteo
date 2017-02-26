#pragma once

#include <stddef.h>

class Slide {
public:
  virtual bool update() = 0;

  virtual const char *line(size_t line) const = 0;
  virtual size_t rows() const = 0;
};
