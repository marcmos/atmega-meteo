#include "LCD.hpp"

bool LCD::display(Slide *slide) {
  if(!slide->update())
    return false;

  for(size_t row = 0; row < slide->rows(); ++row) {
    print(slide->line(row));
    print("\n");
  }

  return true;
}
