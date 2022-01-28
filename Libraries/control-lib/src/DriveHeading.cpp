#include <DriveHeading.h>

void DriveHeading::processError(float error)
{

    float effort = pidDriveHeading.computeEffort(error); //Use of controller with error getting passed directly

    leftEffort = effort;
    rightEffort = effort;
    
}