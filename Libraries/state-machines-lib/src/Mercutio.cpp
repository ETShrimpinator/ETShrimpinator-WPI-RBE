#include <Mercutio.h>

void Mercutio::init() {

robot.init(enableLED, enableIREmitter, enableRangefinder, enableIMU, enableIRPositionSensor);

}

void Mercutio::runStateMachine() {

switch(currentState) {

    case IDLE:
        robot.stop();
        
        break;
    case CIRCLING:
        robot.
        break;
    case TURN_TO_CHARGE:
        break;
    case CHARGE:
        break;
    case DIES1:
        break;
    case DIES2:
        break;
    case DIES3:
        break;
    default:
        break;

  }

}