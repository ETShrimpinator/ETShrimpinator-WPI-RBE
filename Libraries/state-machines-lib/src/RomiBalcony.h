#pragma once
#include <Arduino.h>
#include <Robot.h>

class RomiBalcony {

    Robot robot;

protected:

    enum ROBOT_STATE{   
                    IDLE, 
                    FINDING_JULIET,
                    FOLLOW_JULIET_IR,
                    FOLLOW_JULIET_COMBO,
                    TURN_TO_JULIET,
                    KISS_JULIET,
                    };

    ROBOT_STATE currentState = IDLE;

    bool enableLED = true;
    bool enableIREmitter = false;
    bool enableRangefinder = true;
    bool enableIMU = false;
    bool enableIRPositionSensor = true;
    bool enableCamera = false;
 
public: 

    bool julietReady = false;
    float julietXPos;

    RomiBalcony();
    void init();
    void runStateMachine();

};