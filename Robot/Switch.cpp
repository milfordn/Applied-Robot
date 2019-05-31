#include "Switch.h"

Switch::Switch(uint8_t pin){
  pinMode(pin, INPUT_PULLUP);
  this->setInverted(false);
}

void Switch::setInverted(bool invert){
  this->inverted = invert;
}

bool Switch::pressed(){
  if(inverted)
    return !digitalRead(pin);
  return digitalRead(pin);
}
