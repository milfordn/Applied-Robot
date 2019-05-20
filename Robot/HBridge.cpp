#include "HBridge.h"

HBridge::HBridge(byte en, byte in1, byte in2){
    this->pin_en = en;
    this->pin_in1 = in1;
    this->pin_in2 = in2;

    pinMode(pin_en, OUTPUT);
    pinMode(pin_in1, OUTPUT);
    pinMode(pin_in2, OUTPUT);
    
    analogWrite(pin_en, 0);
}

void HBridge::drive(short vel){
    if(vel < 0){
      vel *= -1;
      digitalWrite(pin_in1, HIGH);
      digitalWrite(pin_in2, LOW);
    }
    else{
      digitalWrite(pin_in1, LOW);
      digitalWrite(pin_in2, HIGH);
    }
    analogWrite(pin_en, (byte)vel);
}

void HBridge::brake(){
    analogWrite(pin_en, 255);
    digitalWrite(pin_in1, HIGH);
    digitalWrite(pin_in2, HIGH);
}