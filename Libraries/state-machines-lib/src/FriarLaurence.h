#pragma once
#include <Arduino.h>
#include <Robot.h>

class FriarLaurence {

    Robot robot;

protected:

    enum ROBOT_STATE{   
                    IDLE,
                    ADDRESSJULIET,
                    ADDRESSROMI,
                    };

    ROBOT_STATE currentState = IDLE;

    bool enableLED = true;
    bool enableIREmitter = false;
    bool enableRangefinder = false;
    bool enableIMU = false;
    bool enableIRPositionSensor = false;
    bool enableCamera = false;

public:

    bool coupleReady = false;
    bool friarAddressed = false;
    int lastState = 0;

    FriarLaurence();
    void init();
    void runStateMachine();

};