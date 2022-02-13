#include <Juliet.h>

void Juliet::init() {

robot.init(enableLED, enableIREmitter, enableRangefinder, enableIMU, enableIRPositionSensor);

}

void Juliet::runStateMachine() {

    client.publish("team20/julietTopRamp", String(julietTopRamp).c_str());
    client.publish("team20/julietBottomRamp", String(julietBottomRamp).c_str());
    client.publish("team20/atFriar", String(atFriar).c_str());

switch(currentState) {

    case APPROACHING_RAMP:
        break;
    case UP_RAMP:
        break;
    case SIGNAL:
        break;
    case BEGIN_DESCENT:
        break;
    case DOWN_RAMP:
        break;
    case TURN_AROUND:  
        break;
    case FIND_FRIAR:
        break;
    case KISS_ROMI:
    
    default:
        break;

  }

}