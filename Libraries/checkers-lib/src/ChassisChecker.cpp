#include <ChassisChecker.h>

void ChassisChecker::InitializeChassis() {

chassis.init();

}

bool ChassisChecker::checkChassis() {

    /**
     * Here we check if the motors/pose were recently updated.
     * If so, then call handleUpdateReady(), which does additional tasks
     */
    if(chassis.readyForUpdate) return true;

}

bool ChassisChecker::checkDestination() {

float error = (sqrt((finalPose.x-destPose.x)*(finalPose.x-destPose.x)+(finalPose.y-destPose.y)*(finalPose.y-destPose.y)));

	if (error < 4) return true; // within range
	else return false;

}

bool ChassisChecker::checkHeading() {

float error = (sqrt((finalPose.x-destPose.x)*(finalPose.x-destPose.x)+(finalPose.y-destPose.y)*(finalPose.y-destPose.y)));

	if (error < 4) return true; // within range
	else return false;

}

bool ChassisChecker::checkArc() {

float error = (sqrt((finalPose.x-destPose.x)*(finalPose.x-destPose.x)+(finalPose.y-destPose.y)*(finalPose.y-destPose.y)));

	if (error < 4) return true; // within range
	else return false;

}