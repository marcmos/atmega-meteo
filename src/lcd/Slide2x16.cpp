#include "Slide2x16.hpp"

Slide2x16::Slide2x16(const char *line1, const char *line2) {
  lines[0] = line1;
  lines[1] = line2;
}

bool Slide2x16::update() {
  return true;
}

inline const char *Slide2x16::line(size_t line) const {
  return lines[line];
}

inline size_t Slide2x16::rows() const {
  return 2;
}
