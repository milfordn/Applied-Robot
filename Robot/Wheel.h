#ifndef WHEEL_H
#define WHEEL_H

#include <Arduino.h>

class Wheel{
private:
    int pin_en, pin_in1, pin_in2;
    int pin_enc_a, pin_enc_b;

    long encoderTime, encoderTimeLast;
    short encoderTicks = 0;
    int encoderDir = 0;

    void detachEncoderISR();

    //Don't question it
    static Wheel *registeredLeft, *registeredRight;
    static void leftEncoderISR();
    static void rightEncoderISR();
    static void generalISR(Wheel * wheel);
public:
    static void registerLeftRight(Wheel * left, Wheel * right);
    Wheel(int en, int in1, int in2, int enc_a, int enc_b);
    ~Wheel();

    //vel is within [-255..255]
    void drive(short vel);
};

#endif