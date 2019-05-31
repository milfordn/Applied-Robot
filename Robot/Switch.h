#ifndef SWITCH_H
#define SWITCH_H

#include <Arduino.h>

class Switch{
public:
  Switch(uint8_t PIN);
  void setInverted(bool invert);
  bool pressed();
private:
  bool inverted;
  uint8_t pin;
};

#endif
