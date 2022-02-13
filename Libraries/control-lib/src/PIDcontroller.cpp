#include <PIDcontroller.h>
#include <math.h>

PIDController::PIDController(float newKp, float newKi, float newKd, float newSetpoint, float newBaseEffort, int newConfig) {

    kp = newKp;
    ki = newKi;
    kd = newKd;
    setpoint = newSetpoint;
    baseEffort = newBaseEffort;
    config = newConfig;

}


float PIDController::computeEffort(float error)
{
    currError = error; //store in case we want it later
    sumError += currError;

    if(errorBound > 0) //cap error; errorBound == 0 means don't cap
    {
        if(fabs(sumError) > errorBound) //you could multiply sumError by Ki to make it scale
        {
            sumError -= currError; //if we exceeded the limit, just subtract it off again
        }
    }

    float derivError = currError - prevError;
    prevError = currError;

    currEffort = kp * currError + ki * sumError + kd * derivError;

    return currEffort;
}

void PIDController::processInput(float processVariable) {

    float error = processVariable - setpoint;
    float effort = computeEffort(error);

if (config == 1) {  //Enum this, for standoff

    leftEffort = effort;
    rightEffort = effort;
}

else if (config == 2) {

    leftEffort = baseEffort - effort; //For wall on left side of robot,
    rightEffort = baseEffort + effort;

}

else if (config == 3) {

    leftEffort = baseEffort + effort; //For wall on right side of robot, aprilTags, and IRbeacons.
    rightEffort = baseEffort - effort;

}

}
