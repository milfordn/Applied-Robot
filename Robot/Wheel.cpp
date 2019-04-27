#include "Wheel.h"

Wheel * Wheel::registeredLeft = NULL;
Wheel * Wheel::registeredRight = NULL;

Wheel::Wheel(int en, int in1, int in2, int enc_a, int enc_b){
    pin_en = en;
    pin_in1 = in1;
    pin_in2 = in2;
    pin_enc_a = enc_a;
    pin_enc_b = enc_b;

    pinMode(pin_en, OUTPUT);
    pinMode(pin_in1, OUTPUT);
    pinMode(pin_in2, OUTPUT);
    pinMode(pin_enc_a, INPUT);
    pinMode(pin_enc_b, INPUT);

    analogWrite(pin_en, 0);

    digitalWrite(pin_enc_b, LOW);
    encoderTime = micros();
    encoderTimeLast = encoderTime - 1000;
}

void Wheel::detachEncoderISR(){
    detachInterrupt(digitalPinToInterrupt(pin_enc_a));
}

Wheel::~Wheel(){
    detachEncoderISR();
}

void Wheel::drive(short vel){
    if(vel < 0){
      vel *= -1;
      digitalWrite(pin_in1, HIGH);
      digitalWrite(pin_in2, LOW);
    }
    else{
      digitalWrite(pin_in1, LOW);
      digitalWrite(pin_in2, HIGH);
    }
    analogWrite(pin_en,vel);
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