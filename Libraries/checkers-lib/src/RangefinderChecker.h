#pragma once

#include <HCSR04.h>

#define HC_TRIG 16   //for pinging -- not a great choice since this can hamper uploading
#define HC_ECHO 17   //for reading pulse

class RangefinderChecker {

    HCSR04 rangefinder = HCSR04(HC_ECHO, HC_TRIG);

public:

    void initializeRangefinder();
    float checkRangefinder();
    float distanceReading = 0;

};