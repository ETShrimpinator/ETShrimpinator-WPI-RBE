#include <Chassis.h>

#include <Pose.h>
#include <IRCodes.h>

#include <HCSR04.h>
#include <IRdecoder.h>
#include <BNO055.h>
#include <IRDirectionFinder.h>
#include <OpenMV.h>
#include <LED.h>
#include <IREmitter.h>
#include <PIDcontroller.h>
#include <Filter.h>

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
                                //(Kp, Ki, Kd, Setpoint, BaseEffort, Config);
    PIDController wallFollowerLeft = PIDController(1, 0, 0.1, 10, 15, 2); //For forwards up ramp
    PIDController wallFollowerRight = PIDController(1, 0, 0.1, 10, 15, 3); //For reverse down ramp
    PIDController standoff = PIDController(2, 0, 0, 5, 0, 1); //For murder
    PIDController aprilTagFollower = PIDController(0.6, 0, 0.05, 80, 15, 3); //For tracking for murder and finding friar laurence
    PIDController irPointTracker = PIDController(0.6, 0, 0.05, 64, 0, 3); //For waiting to murder and tracking juliet
    PIDController driveDistanceCtrl = PIDController(3.5, 0, 0, 0, 0, 1);
    PIDController driveHeadingCtrl = PIDController(6, 0, 0, 0, 0, 1);
    PIDController driveArcCtrl = PIDController(2, 0, 0, 0, 0, 1);

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
    void Robot::pulseLED(int rate) { led.pulse(rate); }
    bool Robot::checkIRReciever(void) { if (digitalRead(IR_PIN) == 0) return true; }

    int16_t checkIRPress();
    float checkRangefinder();
    bool checkChassis();
    bool checkIMU();
    bool checkBump();
    int16_t checkIRPositionFinder();
    uint16_t checkCamera();

    bool loopsComplete();

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
    void setTargetTurnLocal(float targetTheta);
    bool checkDestination();
    bool checkHeading();
    bool checkArc();
    void resetPose();
    void updatePose(float leftDelta, float rightDelta);
    void printPose();

};