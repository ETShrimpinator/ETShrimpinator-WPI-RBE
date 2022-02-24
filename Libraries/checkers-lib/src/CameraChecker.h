#include <OpenMV.h>

class CameraChecker {
    
    OpenMV camera;
    AprilTagDatum tag;

public:

    uint16_t checkCamera();

};