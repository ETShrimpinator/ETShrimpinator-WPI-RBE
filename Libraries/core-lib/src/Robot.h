#include <Chassis.h>

#include <WallFollower.h>
#include <WallFollowerReverse.h>
#include <Standoff.h>
#include <AprilTagFollower.h>
#include <DriveDistance.h>
#include <DriveHeading.h>
#include <DriveArc.h>

#include <Pose.h>
#include <IRCodes.h>

#include <HCSR04.h>
#include <IRdecoder.h>
#include <BNO055.h>
#include <IRDirectionFinder.h>
#include <OpenMV.h>
#include <LED.h>
#include <IREmitter.h>

#include <MQTT.h>
#include <math.h>

#define WHEEL_TRACK	14.0 //cm
#define WHEEL_RADIUS 3.5 //cm
#define IR_PIN 15
#define HC_TRIG 16   //for pinging -- not a great choice since this can hamper uploading
#define HC_ECHO 17   //for reading pulse
#define LED_PIN 18
#define EMITTER_PIN 19

class Robot {
    
protected:
    Chassis chassis;
    
    WallFollower wallFollower;
    WallFollowerReverse wallFollowerReverse;
    Standoff standoff;
    AprilTagFollower aprilTagFollower;
    IRPointFollower irPointFollower;

    DriveDistance driveDistance;
    DriveHeading driveHeading;
    DriveArc driveArc;

    Filter filter;

    HCSR04 rangefinder;
    IRDecoder irDecoder;
    BNO055 imu;
    IRDirectionFinder irPositionSensor;
    OpenMV camera;
    LED led;
    IREmitter irEmitter;

public:
    
protected:
    float wheelRadius = WHEEL_RADIUS;
    float wheelTrack = WHEEL_TRACK;
    float sumDistError = 0;
    float prevDistError = 0;
    float errorBoundDist = 0;
    float sumAngleError = 0;
    float prevAngleError = 0;
    float errorBoundAngle = 0;
    float kpDist = 3.5;
    float kiDist = 0;
    float kdDist = 0;
    float kpAngle = 6;
    float kiAngle = 0;
    float kdAngle = 0;
    float estimatedPitchAngle = 0;

public:
    bool sceneStart = false;
    float pitchAngle = 0;
    int16_t keyCode;

    Pose initialPose;
    Pose finalPose;
    Pose destPose;
    float targetArcRadius = 0;
    AprilTagDatum tag;

protected:

public:
    Robot(void);
    void init(bool, bool, bool, bool, bool);
    void stop(); 
    void Robot::startIREmitter(void) { irEmitter.pulse(38000); }
    void Robot::stopIREmitter(void) { irEmitter.solidOff(); }
    bool Robot::checkIRReciever(void) { if (digitalRead(IR_PIN) == 0) return true; }

    int16_t checkIRPress();
    float checkRangefinder();
    bool checkChassis();
    bool checkIMU();
    bool checkBump();
    int16_t checkIRPositionFinder();
    uint16_t checkCamera();

    void handleIRPress(int16_t);
    void handleStandoffDistanceReading(float);     
    void handleWallDistanceReading(float, bool);  
    void handleUphillDistanceReading(float);
    void handleUpdatePoint();          
    void handleUpdateHeading();
    void handleUpdateArc();
    float handleIMUPitch();
    float handleIMUYaw(void);   
    void handleIRPosition();         
    void handleNewImage(void);

    void setTargetPose(float, float);
    void setTargetTurn(float);
    void setTargetArc(float);
    void setTargetPoseLocal(float, float);
    void setTargetTurnLocal(float, float);
    bool checkDestination();
    bool checkHeading();
    bool checkArc();
    void resetPose();
    void updatePose();
    void printPose();

};