#ifndef WHEEL_H
#define WHEEL_H

#define WHEEL_DIAMETER 7 //inches
#define TICKS_PER_REV 8

#include <Arduino.h>

class Wheel{
private:
    byte pin_en, pin_in1, pin_in2;
    byte pin_enc_a, pin_enc_b;

    long encoderTime, encoderTimeLast;
    short encoderTicks = 0;
    byte encoderDir = 0;

    void detachEncoderISR();

    //Don't question it
    static Wheel *registeredLeft, *registeredRight;
    static void leftEncoderISR();
    static void rightEncoderISR();
    static void generalISR(Wheel * wheel);
public:
    static void registerLeftRight(Wheel * left, Wheel * right);
    Wheel(byte en, byte in1, byte in2, byte enc_a, byte enc_b);
    ~Wheel();
    void drive(short vel);    //vel is within [-255..255]
    void brake();
    float getSpeed();
    float getDistance();
};

#endif