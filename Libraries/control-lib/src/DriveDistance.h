#include <PIDcontroller.h>

class DriveDistance
{
public:
    float leftEffort = 0;
    float rightEffort = 0;

protected:

    PIDController pidDriveDistance;

public:

    DriveDistance(void) : pidDriveDistance(3.5, 0, 0) {} //kp, ki, kd

    void processError(float error);

};