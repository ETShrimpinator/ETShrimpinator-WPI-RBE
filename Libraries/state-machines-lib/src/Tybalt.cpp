#include <Tybalt.h>

void Tybalt::init() {

robot.init(enableLED, enableIREmitter, enableRangefinder, enableIMU, enableIRPositionSensor);

}

void Tybalt::runStateMachine() {

    client.publish("team20/mercutioDead", String(mercutioDead).c_str());

switch(currentState) {

    case IDLE:
        if (tybaltDead == true) currentState = DIES1;
        robot.stop();
        break;
    case FOLLOWING_MERCUTIO:
        robot.handleNewImage();
        robot.pulseLED(750);
        if (robot.loopsComplete()) currentState = CHARGE_MERCUTIO;
        break;
    case CHARGE_MERCUTIO:
        float distance = robot.checkRangefinder();
        robot.handleStandoffDistanceReading(distance);
        robot.pulseLED(500);
        if(distance < 5) currentState = IDLE; mercutioDead = true;
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
        if (robot.checkDestination()) currentState = IDLE;
        break;
    default:
    break;

  }

}
