#include "PIDF.h"

PIDF::PIDF(float p, float i, float d, float f, float highLimit, float lowLimit){
    kp = p;
    ki = i;
    kd = d;
    kf = f;
    lower = lowLimit;
    higher = highLimit;
}

float PIDF::get(float dt, float set, float get, float d){
    //TODO:: Double check this
    float error = set - get;
    accumulatedError += error  * dt;
    float output = error * kp + accumulatedError * ki + set * kf;

    if(!isnan(upper) && output > upper){
        accumulatedError = (upper - (error * kp + set * kf)) / ki; //back-calculate what error should be at this point
        if(accumulatedError < 0) accumulatedError = 0;
    }
    if(!isnan(lower) && output < lower){
        integral = (lower - (error * kp + set * kf)) / ki;
        if(accumulatedError < 0) accumulatedError = 0;
    }

    return error * kp + accumulatedError * ki + d * kd;
}
    
    
