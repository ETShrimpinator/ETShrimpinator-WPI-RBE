#include <PIDcontroller.h>
#include <Filter.h>

class AprilTagFollower
{
public:
    float leftEffort = 0;
    float rightEffort = 0;

protected:

    float setpoint = 80;
    PIDController pidAprilTagFollower;

public:
    AprilTagFollower(void) : pidAprilTagFollower(0.6, 0, 0.05) {}

    void processImage(float xDis);
};