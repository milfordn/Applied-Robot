#include "RealTimeDelay.h"

void RealTimeDelay::setDelay(uint16_t delayAmount){
    this->delayAmount = delayAmount;
}

bool RealTimeDelay::complete(){
    return millis() - resetTime > delayAmount;
}

void RealTimeDelay::reset(){
    resetTime = millis();
}