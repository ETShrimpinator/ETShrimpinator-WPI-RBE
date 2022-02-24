#include <Chassis.h>
#include <math.h>

Chassis::Chassis(void) :
    leftMotor(MOTOR_LEFT_PWM, MOTOR_LEFT_DIR, MOTOR_LEFT_ENCA, MOTOR_LEFT_ENCB),
    rightMotor(MOTOR_RIGHT_PWM, MOTOR_RIGHT_DIR, MOTOR_RIGHT_ENCA, MOTOR_RIGHT_ENCB)
{}

void Chassis::init(void) {

	allocateTimer(); // used by the DC Motors

	leftMotor.attach();
    rightMotor.attach();

	stop();

}

void Chassis::setWheelSpeeds(float left, float right) {

    leftMotor.setTargetDegreesPerSecond(left);
    rightMotor.setTargetDegreesPerSecond(right);

}

void Chassis::setMotorEfforts(float left, float right)  {

    leftMotor.setEffortPercent(left);
    rightMotor.setEffortPercent(right);

}

void Chassis::motorHandler(void) {

    if(!timerAllocated) allocateTimer();

	if(++velocityLoopCounter == controlIntervalMS) {

		velocityLoopCounter = 0;

		leftMotor.process();
		rightMotor.process();

		leftDelta = leftMotor.getDelta();
		rightDelta = rightMotor.getDelta();

		readyForUpdate = true; 

	}

}

static TaskHandle_t complexHandlerTask;

void onMotorTimer(void* param) {

	ESP_LOGI(TAG, "Starting the PID loop thread");
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
    const TickType_t xInterval = 1; 	// sets up 1ms timer
	while(true)
	{
		vTaskDelayUntil(&xLastWakeTime, xInterval);
		Chassis* pChassis = (Chassis*) param;
		if(pChassis) pChassis->motorHandler();
		else Serial.println("NULL pointer in onMotorTimer()!!");
	}
	ESP_LOGE(TAG, "ERROR PID thread died!");
}

void Chassis::allocateTimer(void)
{
	if (!timerAllocated)
	{
		xTaskCreatePinnedToCore(onMotorTimer, "PID loop Thread", 8192, this, 1, &complexHandlerTask, 0);
	}

	timerAllocated = true;
}