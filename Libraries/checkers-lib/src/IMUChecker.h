#include <BNO055.h>

class IMUChecker {
    
    BNO055 imu;

public:

    uint8_t initalizeIMU();
    bool checkIMU();
    bool checkBump();
    float checkPitch();
    float checkYaw();   
       
    float pitchAngle = 0;
    float yawAngle = 0;

};