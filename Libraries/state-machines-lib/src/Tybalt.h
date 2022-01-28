#pragma once
#include <Arduino.h>
#include <Robot.h>

class Tybalt {

protected:

    enum ROBOT_STATE{   
                    IDLE, 
                    FOLLOWING_MERCUTIO_OPENMV,
                    CHARGE_MERCUTIO,
                    DIES1,
                    DIES2,
                    DIES3,
                    };

    ROBOT_STATE currentState = IDLE;

    bool enableLED = true;
    bool enableIREmitter = true;
    bool enableRangefinder = true;
    bool enableIMU = false;
    bool enableIRPositionSensor = false;
    bool enableCamera = true;

    Robot robot;
    
public: 

   bool mercutioDead = false;
   bool romiFightReady = false;

public:
    void init();
    void runStateMachine();
}