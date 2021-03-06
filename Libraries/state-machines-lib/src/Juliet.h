#pragma once
#include <Arduino.h>
#include <Robot.h>

class Juliet {

    Robot robot;

protected:

    enum ROBOT_STATE{   
                    APPROACHING_RAMP,
                    UP_RAMP,
                    SIGNAL,
                    BEGIN_DESCENT,
                    DOWN_RAMP,
                    TURN_AROUND,
                    FIND_FRIAR,
                    KISS_ROMI,
                    };

    ROBOT_STATE currentState = APPROACHING_RAMP;

    bool enableLED = true;
    bool enableIREmitter = true;
    bool enableRangefinder = true;
    bool enableIMU = true;
    bool enableIRPositionSensor = false;
    bool enableCamera = true;

public:

    bool julietTopRamp = false;
    bool julietBottomRamp = false;
    bool atFriar = false;
    bool friarReady = false;

    float distance = 0;
    float currentPitch = 0;
    float lastPitch = 0;

    Juliet();
    void init();
    void runStateMachine();
    
};