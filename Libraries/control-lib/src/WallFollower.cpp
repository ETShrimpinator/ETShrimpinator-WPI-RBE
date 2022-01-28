#include <WallFollower.h>
#include <IRCodes.h>

void WallFollower::processDistanceReading(float distance)
{
    float error = distance - targetDistance;
    float effort = pidWallFollowerReverse.computeEffort(error);

    leftEffort = (baseEffort - effort);
    rightEffort = (baseEffort + effort);
    
}

void WallFollower::handleKeyPress(int16_t key)
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