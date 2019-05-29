#include "Wheel.h"

Wheel * Wheel::registeredLeft = NULL;
Wheel * Wheel::registeredRight = NULL;

Wheel::Wheel(byte en, byte in1, byte in2, byte enc_a, byte enc_b) : HBridge(en, in1, in2) {
    pin_enc_a = enc_a;
    pin_enc_b = enc_b;

    pinMode(pin_enc_a, INPUT);
    pinMode(pin_enc_b, INPUT);

//    digitalWrite(pin_enc_b, LOW);
//    digitalWrite(pin_enc_a, LOW);
    encoderTime = micros();
    encoderTimeLast = encoderTime - 250;
}

void Wheel::detachEncoderISR(){
    detachInterrupt(digitalPinToInterrupt(pin_enc_a));
}

Wheel::~Wheel(){
    detachEncoderISR();
}

float Wheel::getSpeed(){
    bool encoderUpdated = false;
    float vel;
    do {
        //inches / second = (inches / tick) * (tick / second) = (inches / tick) / (second / tick)
        vel = inchesPerTick / ((encoderTime - encoderTimeLast) / 1000000.);
     } while(encoderUpdated); //re-calculate if an interrupt happened during the calculations
    return vel;
}

float Wheel::getDistance(){
    return getTicks() * inchesPerTick;
}

int16_t Wheel::getTicks(){
//  if(this == Wheel::registeredRight)
//    return encoderTicks / 10;
  return encoderTicks;
}

void Wheel::generalISR(Wheel * wheel){
    wheel->encoderTimeLast = wheel->encoderTime;
    wheel->encoderTime = micros();

    //  A   B   Direction
    //  1   1   -1
    //  1   0   1
    //  0   1   1
    //  0   0   -1
    wheel->encoderDir = (digitalRead(wheel->pin_enc_a) ^ digitalRead(wheel->pin_enc_b)) * 2 - 1;
    wheel->encoderTicks += wheel->encoderDir;
    wheel->encoderUpdated = true;
}

void Wheel::leftEncoderISR(){
    generalISR(Wheel::registeredLeft);
}

void Wheel::rightEncoderISR(){
    generalISR(Wheel::registeredRight);
}

void Wheel::registerLeftRight(Wheel * left, Wheel * right){
    if(Wheel::registeredLeft){
        Wheel::registeredLeft->detachEncoderISR();
    }
    if(Wheel::registeredRight){
        Wheel::registeredRight->detachEncoderISR();
    }

    Wheel::registeredLeft = left;
    Wheel::registeredRight = right;

    attachInterrupt(digitalPinToInterrupt(left->pin_enc_a), Wheel::leftEncoderISR, CHANGE);
    attachInterrupt(digitalPinToInterrupt(right->pin_enc_a), Wheel::rightEncoderISR, CHANGE);
}
