#include <RomiBalcony.h>

void RomiBalcony::init() {

robot.init(enableLED, enableIREmitter, enableRangefinder, enableIMU, enableIRPositionSensor);

}

void RomiBalcony::runStateMachine() {

switch(currentState) {

    case IDLE:
        break;
    case FINDING_JULIET:
        break;
    case FOLLOW_JULIET_IR:
        break;
    case FOLLOW_JULIET_COMBO:
        break;
    case TURN_TO_JULIET:
        break;
    case KISS_JULIET:
    default:
    break;

  }

}