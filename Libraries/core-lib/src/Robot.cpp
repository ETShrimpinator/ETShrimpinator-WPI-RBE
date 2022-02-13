#include <Robot.h>

Robot::Robot(void)

    :filter(5), rangefinder(HC_ECHO, HC_TRIG), irDecoder(IR_PIN) {}
    //nothing to see here; move along...

void Robot::init(bool enableLED, bool enableIREmitter, bool enableRangefinder, bool enableIMU, bool enableIRPositionSensor) {

    chassis.init();
    irDecoder.init();
    if (enableLED) led.init(LED_PIN);
    if (enableIREmitter) irEmitter.init(EMITTER_PIN);
    if (enableRangefinder) rangefinder.init(USE_ECHO | USE_CTRL_PIN);
    if (enableIMU) {
        imu.init(OPR_MODE_AMG, 36);
        imu.enableExternalCrystal(true);
        imu.enableHighAccInterupt(16, 2);  //16 and 2 control how sensitive to bumps
    }
    if (enableIRPositionSensor) irPositionSensor.begin();

}

void Robot::stop() {

    chassis.setMotorEfforts(0,0);

}

int16_t Robot::checkIRPress() {

//check the IR remote
    keyCode = irDecoder.getKeyCode();
    if(keyCode != -1) return keyCode;
    else return -1;

}

float Robot::checkRangefinder() {

//check if time to send ping
    rangefinder.checkPingTimer();

    /** Check the distance sensor.
     * We return true only if there is a new reading, which is passed by reference.
     * It hardly needs to be done this way, but passing by reference is a useful tool,
     * so we start with a 'lightweight' example here.
     */
    float distanceReading = 0;
    bool hasNewReading = rangefinder.getDistance(distanceReading);
    if(hasNewReading) return distanceReading;

}

bool Robot::checkChassis() {

    /**
     * Here we check if the motors/pose were recently updated.
     * If so, then call handleUpdateReady(), which does additional tasks
     */
    if(chassis.readyForUpdate) return true;

}

bool Robot::checkIMU() {

    uint32_t currTime = millis();
    static uint32_t lastIMURead = 0;

    if (currTime - lastIMURead >= 10) { //Testing 10ms

        lastIMURead = currTime;
        return true;

    }

}

bool Robot::loopsComplete() {

    uint32_t currTime = millis();
    static uint32_t lastTime = 0;

    if (currTime - lastTime >= 20000) {

        lastTime = currTime;
        return true;

    }

}

bool Robot::checkBump() {

    if(imu.imuInt) {

    Serial.println("bump!");
    imu.resetInterrupt();
    return true;

    }

}

int16_t Robot::checkIRPositionFinder() {

  Point point;

  /*!
   *  @brief request the position
   */
  irPositionSensor.requestPosition();
  /*!
   *  @brief If there is data available, print it. Otherwise show the error message.
   */
  if (irPositionSensor.available()) {
    for (int i=0; i<4; i++) 
    {
      point = irPositionSensor.ReadPoint(i);
      //Serial.print(point.x);
      //Serial.print(",");
      
      //Serial.print(point.y);
      //Serial.print(";");

    }

    //Serial.print('\n');
    return point.x;

  }

  else Serial.println("Device not available!");

}


uint16_t Robot::checkCamera() {


  if(camera.checkUART(tag))
  {
    Serial.print(F("Tag [cx="));
    Serial.print(tag.cx);
    Serial.print(F(", cy="));
    Serial.print(tag.cy);
    Serial.print(F(", w="));
    Serial.print(tag.w);
    Serial.print(F(", h="));
    Serial.print(tag.h);
    Serial.print(F(", id="));
    Serial.print(tag.id);
    Serial.print(F(", rot="));
    Serial.print(tag.rot);
    Serial.println(F("]"));
    return tag.cx;
  }

  return 0;
}

void Robot::handleIRPress(int16_t key) {



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

void Robot::handleUpdatePoint() { //This gets called whenever the drive motors and pose get updated.

    chassis.readyForUpdate = false; //Does this work???
    printPose(); //make function

        if (checkDestination()) chassis.stop();
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

void Robot::handleUpdateHeading() {



}

void Robot::handleUpdateArc() {



}

float Robot::handleIMUPitch(void) {

 vector<int16_t> acc = imu.readRawAcc();
 vector<int16_t> gyro = imu.readRawGyro();

    float gyroBias;
    float accY = (((acc[1]) - 37.8) / 1000.0);  //Divide by 1000 to get from LSB to Gs, apply offsets found in testing.
    float accZ = (((acc[2]) + 57.2) / 1000.0);
    float gyroX = (gyro[0]/900.0);  //Divide by 16 for degrees per second, divide by 900 for rad/s.
  
    float observedAngle = atan2(accY, accZ)* (-1.0);  //Accelerometer
    float predictedAngle = pitchAngle + (0.005 / 900.0) * (gyro[0] - gyroBias); //Gyro, includes bias calculation.
    static float kap = 0.05; //Ratio of accelerometer to gyro
    static float ep = 0.000001; //Proportional constant of gyro bias correction
    float gyroBias = gyroBias - ep * (900 / 0.005) * (observedAngle - predictedAngle); //Gyro bias
    float pitchAngle = (1 - kap) * predictedAngle + (kap * observedAngle); //Complimentary filter output of pitch angle.
/*
    Serial.print(observedAngle*(180.0/3.14159));
    Serial.print('\t');
    Serial.println(pitchAngle*(180.0/3.14159));   */

    return pitchAngle;

}

float Robot::handleIMUYaw() {

 vector<int16_t> acc = imu.readRawAcc();
 vector<int16_t> gyro = imu.readRawGyro();

    float accX = (((acc[0]) + 2.8) / 1000.0); //Divide by 1000 to get from LSB to Gs, apply offsets found in testing.
    float accY = (((acc[1]) - 37.8) / 1000.0);
    float accZ = (((acc[2]) + 57.2) / 1000.0);

/*
    Serial.print(accX);
    Serial.print('\t');
    Serial.print(accY);
    Serial.print('\t');
    Serial.print(accZ);
    Serial.println('\t');  */

    float gyroX = (gyro[0]/900.0);  //Divide by 16 for degrees per second, divide by 900 for rad/s.
    float gyroY = (gyro[1]/900.0);
    float gyroZ = (gyro[2]/900.0);
/*
    Serial.print(gyroX);
    Serial.print('\t');
    Serial.print(gyroY);
    Serial.print('\t');
    Serial.print(gyroZ);
    Serial.print('\t');    
*/
    float yawAngle = 0;
    return yawAngle;

}

void Robot::handleIRPosition() {



}

void Robot::handleNewImage(void) {

    aprilTagFollower.processInput(tag.cx);
    chassis.setMotorEfforts(aprilTagFollower.leftEffort, aprilTagFollower.rightEffort);

}

void Robot::setTargetPose(float targetX, float targetY) {

	destPose.x = targetX;
	destPose.y = targetY;
	destPose.theta = (atan2(targetY - finalPose.y, targetX - finalPose.x)*(180.0/3.14159)) - 90;

}

void Robot::setTargetTurn(float targetTheta) {

    destPose.x = initialPose.x;
    destPose.y = initialPose.y;
	destPose.theta = targetTheta;

}

void Robot::setTargetArc(float targetRadius) {

    targetArcRadius = targetRadius;

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

bool Robot::checkDestination(void) {

float distError = (sqrt((finalPose.x-destPose.x)*(finalPose.x-destPose.x)+(finalPose.y-destPose.y)*(finalPose.y-destPose.y)));

	if (distError < 4) return true; // within range
	else return false;

}

bool Robot::checkHeading(void) {

float error = (sqrt((finalPose.x-destPose.x)*(finalPose.x-destPose.x)+(finalPose.y-destPose.y)*(finalPose.y-destPose.y)));

	if (error < 4) return true; // within range
	else return false;

}

bool Robot::checkArc(void) {

float error = (sqrt((finalPose.x-destPose.x)*(finalPose.x-destPose.x)+(finalPose.y-destPose.y)*(finalPose.y-destPose.y)));

	if (error < 4) return true; // within range
	else return false;

}

void Robot::resetPose() {

	chassis.stop(); //Does the same thing as robot stop
	initialPose.x = 0;
	initialPose.y = 0;
	initialPose.theta = 0;
	finalPose.x = 0;
	finalPose.y = 0;
	finalPose.theta = 0;

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

void Robot::printPose() {



    
}