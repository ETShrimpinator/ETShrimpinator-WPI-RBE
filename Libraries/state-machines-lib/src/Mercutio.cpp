#include <Mercutio.h>

void Mercutio::init() {

robot.init(enableLED, enableIREmitter, enableRangefinder, enableIMU, enableIRPositionSensor);

}

Mercutio::runStateMachine() {

switch(currentState) {

    case IDLE:
        robot.stop();
        if (robot.Start()) currentState = CIRCLING;
        break;
    case CIRCLING:
        //robot.setTwist(); need a real set twist function that incorporates IMU, or wifi position sharing
        if (wifiTybaltReady()) currentState = CHARGE;
        break;
    case TURN_TO_CHARGE:
        robot.resetPose //Need passthroughreset pose function... the amount of times we do this makes me want to have pose data in robot instead of chassis
        robot.setDestination(-10, 0);
        if (robot.checkDestination()) currentState = CHARGE;
        break;
    case CHARGE:
        //standoff code, ultrasonic should actually be on mercutio?
    
        break;
    case DIES1:
        robot.loop();
        robot.resetPose();
        robot.setDestination(-30,-30);
        break;
    case DIES2:
        break;
        robot.loop();
        robot.resetPose();
        robot.setDestination(-30,-30);
    case DIES3:
        robot.loop();
        robot.resetPose();
        robot.setDestination(-30,-30);
        break;
    default:
        break;

  }

}

bool Mercutio::wifiTybaltReady() {

    tybaltReady = true;
    return tybaltReady;

}