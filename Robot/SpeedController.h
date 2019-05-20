#ifndef SPEED_CONTROLLER_H
#define SPEED_CONTROLLER_H

#include <Arduino.h>

class SpeedController{
private:
    byte pin_en;
public:
    SpeedController(byte en);
    void drive(byte vel);
};

#endif