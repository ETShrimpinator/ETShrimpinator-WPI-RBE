#include <Robot.h>

void Robot::init(bool enableLED, bool enableIREmitter, bool enableRangefinder, bool enableIMU, bool enableIRPositionSensor) {

    chassis.init();
    irRemoteCheck.initializeIRRemote();
    if (enableLED) led.init(18);
    if (enableIREmitter) irEmitter.init(19);
    if (enableRangefinder) rangefinderCheck.initializeRangefinder();
    if (enableIMU) imuCheck.initializeIMU();
    if (enableIRPositionSensor) irPositionCheck.initializeIRPosition();

}

void Robot::stop() {

    chassis.setMotorEfforts(0,0);

}

void Robot::updatePose(float leftDelta, float rightDelta) { //parameters in degrees of wheel rotation 

	float cmPerDegrees = 0.06108652381;
	float wheelTrack = 14; //cm
	float leftRotationalSpeed = chassis.leftMotor.getDelta();
	float rightRotationalSpeed = chassis.rightMotor.getDelta();

	float leftLinearSpeed = leftRotationalSpeed * cmPerDegrees;
	float rightLinearSpeed = rightRotationalSpeed * cmPerDegrees;
	float RobotLinearSpeed = ((rightLinearSpeed + leftLinearSpeed) / 2.0);
	float RobotOmega = (rightLinearSpeed - leftLinearSpeed) / wheelTrack;
	finalPose.theta = RobotOmega + initialPose.theta;
	float averageTheta = ((initialPose.theta + finalPose.theta) / 2.0);
	finalPose.x = initialPose.x + ((-1)* (RobotLinearSpeed * sin(averageTheta)));
	finalPose.y = initialPose.y + (RobotLinearSpeed * cos(averageTheta));

	initialPose = finalPose;
	
}

void Robot::setTargetPoseGlobal(float targetX, float targetY) {

	destPose.x = targetX;
	destPose.y = targetY;
	destPose.theta = (atan2(targetY - finalPose.y, targetX - finalPose.x)*(180.0/3.14159)) - 90;

}

void Robot::setTargetTurnGlobal(float targetTheta) {

    destPose.x = initialPose.x;
    destPose.y = initialPose.y;
	destPose.theta = targetTheta;

}

void Robot::setTargetArcGlobal(float targetRadius, float degrees) {

    destPose.x = initialPose.x + targetRadius * cos(degrees);
    destPose.y = initialPose.y + targetRadius * sin(degrees);
    destPose.theta = initialPose.theta + degrees;

}

void Robot::setTargetPoseLocal(float targetX, float targetY) {

    destPose.x = initialPose.x + targetX;
    destPose.y = initialPose.y + targetY;
    destPose.theta = (atan2(targetY, targetX)*(180.0/3.14159)) - 90; //Convert to degrees and orient Y as forwards out of robot.

}

void Robot::setTargetTurnLocal(float targetTheta) {

    destPose.x = initialPose.x;
    destPose.y = initialPose.y;
	destPose.theta = initialPose.theta + targetTheta;

}

void Robot::setTargetArcLocal(float radius, float degrees) {

    destPose.x = initialPose.x + radius * cos(degrees);
    destPose.y = initialPose.y + radius * sin(degrees);
    destPose.theta = initialPose.theta + degrees;

}

void Robot::handleUpdateHeading() {

    if (chassisCheck.checkDestination()) chassis.stop();
    else { 
        float currAngleError = finalPose.theta - destPose.theta;
    
    driveHeadingCtrl.processInput(currAngleError);

    float leftSp = driveHeadingCtrl.leftEffort;
    float rightSp = driveHeadingCtrl.rightEffort;

    chassis.setWheelSpeeds(leftSp, rightSp);
    }

}

void Robot::handleUpdateArc() {



}

void Robot::handleUpdatePoint() { //This gets called whenever the drive motors and pose get updated.

    chassis.readyForUpdate = false; //Does this work??

        if (chassisCheck.checkDestination()) chassis.stop();
        else { 
            
float currDistError = (sqrt((finalPose.x-destPose.x)*(finalPose.x-destPose.x)+(finalPose.y-destPose.y)*(finalPose.y-destPose.y)));
float currAngleError = destPose.theta - (finalPose.theta * (180.0/3.14159));

driveDistanceCtrl.processInput(currDistError);
driveHeadingCtrl.processInput(currAngleError);

	float leftSp = driveDistanceCtrl.leftEffort - driveHeadingCtrl.leftEffort;
	float rightSp = driveDistanceCtrl.rightEffort + driveHeadingCtrl.rightEffort;

	    chassis.setWheelSpeeds(leftSp, rightSp); 
        
    }

}

void Robot::handleStandoffDistanceReading(float distanceReading) {

    float averageDist = filter.addAndReturnAverage(distanceReading);
    standoff.processInput(averageDist);
    chassis.setMotorEfforts(standoff.leftEffort, standoff.rightEffort);

}

void Robot::handleWallDistanceReading(float distanceReading, bool reverseDirection) {

    float averageDist = filter.addAndReturnAverage(distanceReading);

    if (reverseDirection == true) {
    wallFollowerRight.processInput(averageDist);  //Calculate efforts for wall following
    chassis.setMotorEfforts(wallFollowerRight.leftEffort, wallFollowerRight.rightEffort); //Apply efforts for wall following
    }
    else {
    wallFollowerLeft.processInput(averageDist);  //Calculate efforts for wall following
    chassis.setMotorEfforts(wallFollowerLeft.leftEffort, wallFollowerLeft.rightEffort); //Apply efforts for wall following
    }
    
}

void Robot::handleUphillDistanceReading(float distanceReading) {

    float averageDist = filter.addAndReturnAverage(distanceReading);
    wallFollowerLeft.processInput(averageDist); //Calculate efforts for wall following
    chassis.setMotorEfforts(wallFollowerLeft.leftEffort + 5, wallFollowerLeft.rightEffort + 5); //Apply efforts for wall following + 5 because uphill.

}

void Robot::handleIRPosition(uint16_t xPos) {

    irPointTracker.processInput(xPos);
    chassis.setMotorEfforts(irPointTracker.leftEffort, irPointTracker.rightEffort);

}

void Robot::handleNewImage(uint16_t xPos) {

    aprilTagFollower.processInput(xPos);
    chassis.setMotorEfforts(aprilTagFollower.leftEffort, aprilTagFollower.rightEffort);

}

void Robot::handleIRPress(int16_t key) {



}

bool Robot::checkChassis() {

    /**
     * Here we check if the motors/pose were recently updated.
     * If so, then call handleUpdateReady(), which does additional tasks
     */
    if(chassis.readyForUpdate) return true;

}

bool Robot::checkDestination() {

float error = (sqrt((finalPose.x-destPose.x)*(finalPose.x-destPose.x)+(finalPose.y-destPose.y)*(finalPose.y-destPose.y)));

	if (error < 4) return true; // within range
	else return false;

}

bool Robot::checkHeading() {

float error = (sqrt((finalPose.x-destPose.x)*(finalPose.x-destPose.x)+(finalPose.y-destPose.y)*(finalPose.y-destPose.y)));

	if (error < 4) return true; // within range
	else return false;

}

bool Robot::checkArc() {

float error = (sqrt((finalPose.x-destPose.x)*(finalPose.x-destPose.x)+(finalPose.y-destPose.y)*(finalPose.y-destPose.y)));

	if (error < 4) return true; // within range
	else return false;

}