#ifndef PID_H
#define PID_H

#include <math.h>

class PIDF{
public:
    PIDF(float p, float i, float d, float f, float highLimit, float lowLimit);
    float get(float dt, float setPoint, float current, float dCurrent);
private:
    float kp, ki, kd, kf;
    float lower = NAN, upper = NAN; 
    float accumulatedError = 0;
};

#endif