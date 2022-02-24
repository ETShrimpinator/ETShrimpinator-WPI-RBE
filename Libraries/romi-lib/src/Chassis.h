#pragma once

#include <RBE-200n-Lib.h>
#include <ESP32Servo.h>
#include <MotorEncoded.h>

class Chassis
{
protected:
	/**
	 * Loop rate for this motor. The main timer loop is 1ms, so this value is in ms.
	 */
	uint32_t controlIntervalMS = DRIVE_MOTOR_CTRL_INT_MS;

	/**
	 * An internal counter that counts iterations of the main motor loop; it is compared to
	 * controlIntervalMS so that the velocity PID runs on longer intervals.
	 */
	uint32_t velocityLoopCounter = 0;

    bool timerAllocated = false;
    void allocateTimer(void); 
    void motorHandler(void);
    friend void onMotorTimer(void* param);
    
public:
    bool readyForUpdate = false;
    float leftDelta = 0;
    float rightDelta = 0;
    MotorEncoded leftMotor;
    MotorEncoded rightMotor;
    
public:
    Chassis(void);

    void init(void);
    void stop(void) {setMotorEfforts(0,0);}
    void setWheelSpeeds(float left, float right);
    void setMotorEfforts(float left, float right);

};
