#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

#include <Arduino.h>

class MotorController{
private:
    byte pin_en, pin_in1, pin_in2;
public:
    MotorController(byte en, byte in1, byte in2);

    // -255 < vel < 255
    void drive(short vel);
    void brake();
};

#endif