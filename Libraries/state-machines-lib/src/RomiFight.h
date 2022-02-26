#pragma once
#include <Arduino.h>
#include <Robot.h>

class RomiFight {

    Robot robot;

    CameraChecker cameraCheck;
    ChassisChecker chassisCheck;
    IMUChecker imuCheck;
    IRPositionChecker irPositionCheck;
    IRRemoteChecker irRemoteCheck;
    RangefinderChecker rangefinderCheck;

protected:

    enum ROBOT_STATE{   
                    IDLE, 
                    FOLLOWING_TYBALT_IR,
                    CHARGE_TYBALT,
                    RUN_AWAY,
                    };

    ROBOT_STATE currentState = FOLLOWING_TYBALT_IR; //Starting state

    bool enableLED = true;
    bool enableIREmitter = false;
    bool enableRangefinder = true;
    bool enableIMU = false;
    bool enableIRPositionSensor = true;
    bool enableCamera = false;

public:

    float tybaltBeacon;
    float distance;

    bool mercutioDead = false;
    bool tybaltDead = false;

    RomiFight();
    void init();
    void runStateMachine();
    
};