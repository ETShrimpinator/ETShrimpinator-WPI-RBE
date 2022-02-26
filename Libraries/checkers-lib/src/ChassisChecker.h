#pragma once

#include <Chassis.h>
#include <Pose.h>

class ChassisChecker {

    Chassis chassis;

    Pose initialPose;
    Pose finalPose;
    Pose destPose;

public:

    void InitializeChassis();
    bool checkChassis();
    bool checkDestination();
    bool checkHeading();
    bool checkArc();

};