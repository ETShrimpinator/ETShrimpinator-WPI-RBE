#include <RangefinderChecker.h>

void RangefinderChecker::initializeRangefinder() {

rangefinder.init(USE_ECHO | USE_CTRL_PIN);

}

float RangefinderChecker::checkRangefinder() {

//check if time to send ping
    rangefinder.checkPingTimer();

    /** Check the distance sensor.
     * We return true only if there  s a new reading, which is passed by reference.
     * It hardly needs to be done this way, but passing by reference is a useful tool,
     * so we start with a 'lightweight' example here.
     */
    bool hasNewReading = rangefinder.getDistance(distanceReading);
    if(hasNewReading) return distanceReading;

}