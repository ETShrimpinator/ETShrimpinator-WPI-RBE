#pragma once
#include <Arduino.h>
#include <Robot.h>
#include <RobotChecker.h>
#include <RobotHandler.h>
#include <RobotSetter.h>

class Tybalt {

protected:

    enum ROBOT_STATE{   
                    IDLE, 
                    FOLLOWING_MERCUTIO,
                    CHARGE_MERCUTIO,
                    DIES1,
                    DIES2,
                    DIES3,
                    };

    ROBOT_STATE currentState = FOLLOWING_MERCUTIO;

    bool enableLED = true;
    bool enableIREmitter = true;
    bool enableRangefinder = true;
    bool enableIMU = false;
    bool enableIRPositionSensor = false;
    bool enableCamera = true;

    Robot robot;
    RobotSetter robotSetter;
    RobotChecker robotChecker;
    RobotHandler robotHandler;

public:

   bool mercutioDead = false;
   bool tybaltDead = false;

public:
    void init();
    void runStateMachine();
    
};