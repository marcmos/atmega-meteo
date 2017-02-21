#include "LCD.hpp"

void LCD::display(const Slide *slide) {
  for(size_t row = 0; row < slide->rows(); ++row) {
    print(slide->line(row));
    print("\n");
  }
}
