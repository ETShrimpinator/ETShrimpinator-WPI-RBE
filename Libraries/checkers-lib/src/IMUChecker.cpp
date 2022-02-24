#include <IMUChecker.h>

uint8_t IMUChecker::initalizeIMU() {

        imu.init(OPR_MODE_AMG, 36);
        imu.enableExternalCrystal(true);
        imu.enableHighAccInterupt(16, 2); 

}

bool IMUChecker::checkIMU() {

    uint32_t currTime = millis();
    static uint32_t lastIMURead = 0;

    if (currTime - lastIMURead >= 10) { //Testing 10ms

        lastIMURead = currTime;
        return true;

    }

}

bool IMUChecker::checkBump() {

    if(imu.imuInt) {

    Serial.println("bump!");
    imu.resetInterrupt();
    return true;

    }

}

float IMUChecker::checkPitch(void) {

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

float IMUChecker::checkYaw() {

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
    return yawAngle;

}