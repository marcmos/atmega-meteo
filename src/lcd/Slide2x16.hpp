#pragma once

#include "Slide.hpp"

class Slide2x16 : public Slide {
public:
  Slide2x16(const char *line1, const char *line2);

  virtual bool update();

  virtual const char *line(size_t line) const;
  size_t rows() const;

private:
  const char* lines[2];
};
