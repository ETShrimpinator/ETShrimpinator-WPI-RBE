#include <Tybalt.h>

void Tybalt::init() {

robot.init(enableLED, enableIREmitter, enableRangefinder, enableIMU, enableIRPositionSensor);

}

Tybalt::runStateMachine() {

    client.publish("team20/mercutioDead", String(mercutioDead).c_str());

switch(currentState) {

    case IDLE:
        robot.stop();
        if ()
        break;
    case FOLLOWING_MERCUTIO_OPENMV
        //need this controller
        if
        else handleState
        break;
    case CHARGE_MERCUTIO:
        if(/*receives wifi flag*/) currentState = DIES1;
        break;
    case DIES1:
        robot.setTargetPoseLocal(-30,-30);
        if (robot.checkChassis()) robot.handleUpdatePoint();
        if (robot.checkDestination()) currentState = DIES2;
        break;
    case DIES2:
        robot.setTargetPoseLocal(0,-60);
        if (robot.checkChassis()) robot.handleUpdatePoint();
        if (robot.checkDestination()) currentState = DIES3;
    case DIES3:
        robot.setTargetPoseLocal(-30,-90);
        if (robot.checkChassis()) robot.handleUpdatePoint();
        if (robot.checkDestination()) currentState = DIES3;
        break;
    default:
    break;

  }

}
