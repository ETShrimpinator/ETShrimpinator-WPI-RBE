#include <PIDcontroller.h>

class DriveArc
{
public:
    float leftEffort = 0;
    float rightEffort = 0;

protected:

    PIDController pidDriveArc;

public:

    DriveArc(void) : pidDriveArc(2, 0, 0) {}

    void processError(float error);

};