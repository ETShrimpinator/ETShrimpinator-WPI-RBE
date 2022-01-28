#include <PIDcontroller.h>

class DriveHeading
{
public:
    float leftEffort = 0;
    float rightEffort = 0;

protected:

    PIDController pidDriveHeading;

public:

    DriveHeading(void) : pidDriveHeading(6, 0, 0) {}

    void processError(float error);

};