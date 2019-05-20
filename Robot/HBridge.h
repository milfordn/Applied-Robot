#ifndef H_BRIDGE_H
#define H_BRIDGE_H

#include <Arduino.h>

class HBridge{
private:
    byte pin_en, pin_in1, pin_in2;
public:
    HBridge(byte en, byte in1, byte in2);

    // -255 < vel < 255
    void drive(short vel);
    void brake();
};

#endif