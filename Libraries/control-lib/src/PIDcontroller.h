#pragma once

#include <Arduino.h>

class PIDController {

public:  //Declare defualt constructor

    PIDController(float newKp,float newKi,float newKd,float newSetpoint,float newBaseEffort, int newConfig);

private:

    int config = 0;

    float kp = 0;
    float ki = 0;
    float kd = 0;
    float processVariable = 0;
    float setpoint = 0;
    float baseEffort = 0;

    float currError = 0;
    float prevError = 0;
    float sumError = 0;
    float errorBound = 0;
    float deltaT = 0; //not used for now; could be useful
    float currEffort = 0;

public:

    float leftEffort = 0;
    float rightEffort = 0;
    static volatile uint8_t readyToPID;   //a flag that is set when the PID timer overflows

public:

    float computeEffort(float error);
    void processInput(float processVariable);

};
