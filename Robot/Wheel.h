#ifndef WHEEL_H
#define WHEEL_H

#define WHEEL_DIAMETER 7 //inches
#define TICKS_PER_REV 374.325 //ticks per output shaft revolution
#define SPROCKET_RATIO 0.5
#define RISING_TO_CHANGE 0.5

#include <Arduino.h>
#include "HBridge.h"

class Wheel : public HBridge{
private:
    byte pin_enc_a, pin_enc_b;

    volatile long encoderTime, encoderTimeLast;
    volatile int16_t encoderTicks = 0;
    volatile int8_t encoderDir = 0;
    volatile bool encoderUpdated;

    void detachEncoderISR();

    //Don't question it
    static Wheel *registeredLeft, *registeredRight;
    static void leftEncoderISR();
    static void rightEncoderISR();
    static void generalISR(Wheel * wheel);
    const float inchesPerTick = PI * WHEEL_DIAMETER / TICKS_PER_REV * SPROCKET_RATIO * RISING_TO_CHANGE;
public:
    static void registerLeftRight(Wheel * left, Wheel * right);
    Wheel(byte en, byte in1, byte in2, byte enc_a, byte enc_b);
    ~Wheel();
    float getSpeed();
    float getDistance();
    int16_t getTicks();
};

#endif
