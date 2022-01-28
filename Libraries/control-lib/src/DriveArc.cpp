#include <DriveArc.h>

void DriveArc::processError(float error)
{

    float effort = pidDriveArc.computeEffort(error); //Use of controller with error getting passed directly

    leftEffort = effort;
    rightEffort = effort;
    
}