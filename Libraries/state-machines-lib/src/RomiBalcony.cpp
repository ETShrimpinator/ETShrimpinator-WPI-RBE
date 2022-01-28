#include <RomiBalcony.h>

void RomiBalcony::init() {

robot.init(enableLED, enableIREmitter, enableRangefinder, enableIMU, enableIRPositionSensor);

}

RomiBalcony::runStateMachine() {

switch(currentState) {

    case IDLE:
        robot.stop();
        if (robot.checkIRReciever()) currentState = FINDING_JULIET;
        break;
    case FINDING_JULIET:
        robot.loop();
        robot.setDestination();
        if (robot.checkDestination()) currentState = FOLLOW_JULIET_IR;
        break;
    case FOLLOW_JULIET_IR:
        julietXPos = robot.checkIRPositionFinder();
        //create a handle IRPositon Finder that corrects and uses a controller based on julietXpos
        if (julietReady) {
            currentState = FOLLOW_JULIET_COMBO;
            julietReady = false;
        }
        break;
    case FOLLOW_JULIET_COMBO:

        julietXPos = robot.checkIRPositionFinder();
        if (robot.checkRangefinder()) {
            distance = robot.checkRangefinder();
            robot.handleWallDistanceReading(distance, true); //update function to handle reverseDirection being true
        }
        if (julietReady) {
            currentState = TURN_TO_JULIET;
            julietReady = fase;
        }
        break;
    case TURN_TO_JULIET:
        robot.resetPose(); //add reset pose function;
        robot.setDestination(30,30);
        if (friarLaurence.friarAddressed) currentState = KISS_JULIET;
        break;
    case KISS_JULIET:
        robot.resetPose();
        robot.setDestination(30,30) //update for actual pose
        if (robot.checkDestination() currentState = IDLE;
    default:
    break;

  }

}

bool RomiBalcony::wifiJulietReady(); {

    julietReady = true;
    return julietReady;

}