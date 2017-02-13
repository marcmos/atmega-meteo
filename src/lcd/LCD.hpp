#pragma once

class LCD {
public:
  virtual void reset() = 0;
  virtual void display(const char* str) = 0;
};
