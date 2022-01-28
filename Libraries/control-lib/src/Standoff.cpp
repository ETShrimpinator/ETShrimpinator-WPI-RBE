#include <Standoff.h>
#include <IRCodes.h>

void Standoff::processDistanceReading(float distance)
{
    float error = distance - targetDistance;
    float effort = pidStandoff.computeEffort(error);

    leftEffort = effort;
    rightEffort = effort;
    
}

void Standoff::handleKeyPress(int16_t key)
{
    switch(key)
    {
        case CHUP:
            targetDistance += 10;
            break;

        case CHDOWN:
            targetDistance -= 10;
            break;

        default:
            if(key >= BUTTON1 && key <= BUTTON9)
            {
                targetDistance = 10 * (key - BUTTON0);
            }
            break;
    }
}