#include <ChassisChecker.h>
#include <CameraChecker.h>
#include <IMUChecker.h>
#include <IRPositionChecker.h>
#include <IRRemoteChecker.h>
#include <RangefinderChecker.h>

#include <IRCodes.h>
#include <Chassis.h>
#include <Filter.h>
#include <Pose.h>
#include <RBE-200n-Lib.h>
#include <LED.h>
#include <IREmitter.h>

#define LED_PIN = 18
#define EMITTER_PIN = 19

class Robot {

    CameraChecker cameraCheck;
    ChassisChecker chassisCheck;
    IMUChecker imuCheck;
    IRPositionChecker irPositionCheck;
    IRRemoteChecker irRemoteCheck;
    RangefinderChecker rangefinderCheck;

    Pose initialPose;
    Pose finalPose;
    Pose destPose;

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
    Chassis chassis;
    LED led;
    IREmitter irEmitter;

public:

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
    float targetArcRadius = 0;

    void init(bool, bool, bool, bool, bool);
    void stop(); 
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
    void updatePose(float leftDelta, float rightDelta);
    void setTargetPoseGlobal(float, float);
    void setTargetHeadingGlobal(float);
    void setTargetArcGlobal(float);
    void setTargetPoseLocal(float, float);
    void setTargetHeadingLocal(float targetTheta);
    bool checkDestination();
    bool checkHeading();
    bool checkArc();
    void resetPose();
    void printPose();

};