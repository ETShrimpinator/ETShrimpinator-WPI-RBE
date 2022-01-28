#include <AprilTagFollower.h>

void AprilTagFollower::processImage(float xDis)
{

    float error = xDis - setpoint;
    float effort = pidAprilTagFollower.computeEffort(error);

    leftEffort = 15 + effort;
    rightEffort = 15 - effort;
    
} 