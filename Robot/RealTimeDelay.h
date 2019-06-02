#ifndef REAL_TIME_DELAY_H
#define REAL_TIME_DELAY_H

#include <Arduino.h>

class RealTimeDelay{
public:
    unsigned long resetTime;
    uint16_t delayAmount; //1 minute-ish max delayAmount
    void reset();
    bool complete();
    void setDelay(uint16_t);
};

#endif