#include <IRPointFollower.h>

void IRPointFollower::processImage(float xDis)
{

    float error = xDis - setpoint;
    float effort = pidIRPointFollower.computeEffort(error);

    leftEffort = 15 + effort;
    rightEffort = 15 - effort;
    
} 