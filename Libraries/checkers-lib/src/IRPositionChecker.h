#pragma once

#include <DFRobotIR.h>

class IRPositionChecker {

    DFRobotIR irPositionSensor;
    Point point;

public:

    void initializeIRPosition();
    int16_t checkIRPosition();

};