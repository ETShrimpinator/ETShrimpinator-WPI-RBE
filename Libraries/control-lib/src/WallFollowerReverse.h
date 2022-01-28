#include <PIDcontroller.h>
#include <Filter.h>

class WallFollowerReverse
{
public:
    float leftEffort = 0;
    float rightEffort = 0;

protected:
    float targetDistance = 10;
    float baseEffort = 15;

    PIDController pidWallFollowerReverse;

public:
    WallFollowerReverse(void) : pidWallFollowerReverse(1, 0, 0.1) {}

    void processDistanceReading(float distance);

};