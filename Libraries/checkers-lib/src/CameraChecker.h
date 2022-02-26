#pragma once

#include <OpenMV.h>
#include <AprilTagDatum.h>

class CameraChecker {
    
    OpenMV camera;
    AprilTagDatum tag;

public:

    uint16_t checkCamera();

};