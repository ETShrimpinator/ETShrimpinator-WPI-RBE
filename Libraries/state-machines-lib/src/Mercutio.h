#pragma once
#include <Arduino.h>
#include <Robot.h>

class Mercutio {

    Robot robot;

protected:

    enum ROBOT_STATE{   
                    IDLE, 
                    CIRCLING,
                    TURN_TO_CHARGE,
                    CHARGE,
                    DIES1,
                    DIES2,
                    DIES3,
                    };

    ROBOT_STATE currentState = CIRCLING;

    bool enableLED = true;
    bool enableIREmitter = false;
    bool enableRangefinder = false;
    bool enableIMU = true;
    bool enableIRPositionSensor = false;
    bool enableCamera = false;

public:

    bool mercutioDead = false;

    Mercutio();
    void init();
    void runStateMachine();
    
};