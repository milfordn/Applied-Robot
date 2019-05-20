#include "SpeedController.h"

SpeedController::SpeedController(byte en){
    this->pin_en = en;

    pinMode(pin_en, OUTPUT);

    analogWrite(pin_en, 0);
}

void SpeedController::drive(byte vel){
    analogWrite(pin_en, 255 - vel);
}