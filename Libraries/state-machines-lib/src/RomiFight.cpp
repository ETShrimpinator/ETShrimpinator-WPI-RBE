#include <RomiFight.h>

void RomiFight::init() {

robot.init(enableLED, enableIREmitter, enableRangefinder, enableIMU, enableIRPositionSensor);

}

void RomiFight::runStateMachine() {

    client.publish("team20/tybaltDead", String(tybaltDead).c_str());

switch(currentState) {

    case IDLE:
        robot.stop();
        if ()
        break;
    case FOLLOWING_TYBALT_IR:
        if(/*wifi flag*/) currentState = CHARGE_TYBALT;
        break;

    case CHARGE_TYBALT:
        if(/*wifi flag*/) currentState = RUN_AWAY;
        else handleState
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