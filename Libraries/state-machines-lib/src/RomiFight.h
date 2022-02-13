#pragma once
#include <Arduino.h>
#include <Robot.h>

class RomiFight {

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

    Robot robot;

public:

    bool mercutioDead = false;
    bool tybaltDead = false;

public:

    void init();
    void runStateMachine();
    
};