#include <RomiFight.h>

void RomiFight::init() {

robot.init(enableLED, enableIREmitter, enableRangefinder, enableIMU, enableIRPositionSensor);

}

void RomiFight::runStateMachine() {

    client.publish("team20/tybaltDead", String(tybaltDead).c_str());

switch(currentState) {

    case IDLE:
        robot.stop();
        break;
    case FOLLOWING_TYBALT_IR:
        robot.handleIRPosition();
        robot.pulseLED(1000);
        if(mercutioDead == true) currentState = CHARGE_TYBALT;
        break;
    case CHARGE_TYBALT:
            float distance = robot.checkRangefinder();
            robot.handleStandoffDistanceReading(distance);
            robot.pulseLED(500);
            if(distance < 5) currentState = RUN_AWAY; tybaltDead = true;
        break;

    case RUN_AWAY:          
        robot.setTargetPoseLocal(-30,-30);
        if (robot.checkChassis()) robot.handleUpdatePoint();
        if (robot.checkDestination()) currentState = IDLE;
        break;
    default:
    break;

  }

}