#include <WallFollowerReverse.h>
#include <IRCodes.h>

void WallFollowerReverse::processDistanceReading(float distance)
{
    float error = distance - targetDistance;
    float effort = pidWallFollowerReverse.computeEffort(error);

    leftEffort = (baseEffort + effort); //reversed from normal wall follower for travelling backwards
    rightEffort = (baseEffort - effort);
    
}