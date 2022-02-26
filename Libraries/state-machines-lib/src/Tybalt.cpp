#include <Tybalt.h>
#include <MQTT.h>

void Tybalt::init() {

robot.init(enableLED, enableIREmitter, enableRangefinder, enableIMU, enableIRPositionSensor);

}

void Tybalt::runStateMachine() {

    client.publish("team20/mercutioDead", String(mercutioDead).c_str());

switch(currentState) {

    case IDLE:
        robot.pulseLED(1500);
        robot.stop();
        if (tybaltDead == true) currentState = DIES1;
        break;
    case FOLLOWING_MERCUTIO:
        mercutioTag = robot.checkCamera();
        robot.handleNewImage(mercutioTag);
        robot.pulseLED(1000);
        if (robot.loopsComplete()) currentState = TURN;
        break;
    case TURN:
        robot.setTargetTurn(90);
        if (robot.checkChassis()) robot.handleUpdateHeading();
        robot.pulseLED(750);
        if (robot.checkHeading()) currentState = CHARGE_MERCUTIO;
        break;
    case CHARGE_MERCUTIO:
        distance = robot.checkRangefinder();
        robot.handleStandoffDistanceReading(distance);
        robot.pulseLED(625);
        if(distance < 5) currentState = IDLE; mercutioDead = true;
        break;
    case DIES1:
        robot.setTargetPoseLocal(-30,-30);
        if (robot.checkChassis()) robot.handleUpdatePoint();
        robot.pulseLED(500);
        if (robot.checkDestination()) currentState = DIES2;
        break;
    case DIES2:
        robot.setTargetPoseLocal(0,-60);
        if (robot.checkChassis()) robot.handleUpdatePoint();
        robot.pulseLED(250);
        if (robot.checkDestination()) currentState = DIES3;
    case DIES3:
        robot.setTargetPoseLocal(-30,-90);
        if (robot.checkChassis()) robot.handleUpdatePoint();
        robot.pulseLED(0);
        break;
    default:
    break;

  }

}