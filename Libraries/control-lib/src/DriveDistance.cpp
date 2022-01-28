#include <DriveDistance.h>

void DriveDistance::processError(float error)
{

    float effort = pidDriveDistance.computeEffort(error); //Use of controller with error getting passed directly

    leftEffort = effort;
    rightEffort = effort;
    
}