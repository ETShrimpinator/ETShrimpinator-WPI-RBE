#include <PIDcontroller.h>
#include <Filter.h>

class Standoff
{
public:
    float leftEffort = 0;
    float rightEffort = 0;

protected:
    float targetDistance = 50;

    PIDController pidStandoff;

public:
    Standoff(void) : pidStandoff(2, 0, 0) {} //TODO: edit gains

    void processDistanceReading(float distance);
    void handleKeyPress(int16_t key);
};