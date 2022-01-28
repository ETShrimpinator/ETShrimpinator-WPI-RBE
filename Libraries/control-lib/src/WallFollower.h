#include <PIDcontroller.h>
#include <Filter.h>

class WallFollower
{
public:
    float leftEffort = 0;
    float rightEffort = 0;

protected:
    float targetDistance = 10;
    float baseEffort = 15;

    PIDController pidWallFollower;

public:
    WallFollower(void) : pidWallFollower(1, 0, 0.1) {}

    void processDistanceReading(float distance);
    void handleKeyPress(int16_t key);
};