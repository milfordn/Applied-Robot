#ifndef PID_H
#define PID_H

class PIDF{
public:
    PIDF(float p, float i, float d, float f, float highLimit, void lowLimit);
    void setpoint(float set);
    void get(float current);
private:
    float kp, ki, kd, kf, lower, upper, accumulatedError;
};

#endif