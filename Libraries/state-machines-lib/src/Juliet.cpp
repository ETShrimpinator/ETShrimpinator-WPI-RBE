#include <Juliet.h>

void Juliet::init() {

robot.init(enableLED, enableIREmitter, enableRangefinder, enableIMU, enableIRPositionSensor);

}

Juliet::runStateMachine() {

    client.publish("team20/julietTopRamp", String(julietTopRamp).c_str());
    client.publish("team20/julietBottomRamp", String(julietBottomRamp).c_str());
    client.publish("team20/atFriar", String(atFriar).c_str());

switch(currentState) {

    case APPROACHING_RAMP:
        if (robot.checkIMU()) currentPitch = robot.handleIMU();
        if (currentPitch < -10) currentState = UP_RAMP;  //Change to climbing once past -10, and sure we're climbing.
        lastPitch = currentPitch;
        if (robot.checkRangefinder()) {
            distance = robot.checkRangefinder(); 
            robot.handleWallDistanceReading(distance, false);
        }
        break;
    case UP_RAMP:
        if(robot.checkImu()) currentPitch = robot.handleIMU();
        if (currentPitch < lastPitch - 10 || currentPitch > lastPitch + 10) currentPitch = lastPitch;
        if (currentPitch > -3) currentState = SIGNALLING;
        lastPitch = currentPitch;
        if (robot.checkRangefinder()) {
            distance = robot.checkRangefinder();
            robot.handleUphillDistanceReading(distance);
        }
        break;
    case SIGNAL:
        julietTopRamp = true;
        robot.startIREmitter();  //Doesn't nessecarily need to be a state, but this lets us set the flag only once.
        currentState = DOWN_RAMP;
        break;
    case BEGIN_DESCENT:
        robot.startIREmitter();
        if(robot.checkImu()) currentPitch = robot.handleIMU();
        if (currentPitch < -10) currentState = DOWN_RAMP;
        lastPitch = currentPitch;
        if (robot.checkRangefinder()) {
            distance = robot.checkRangefinder();
            robot.handleWallDistanceReading(distance, true);
        }
        break;
    case DOWN_RAMP:
        if(robot.checkImu()) currentPitch = robot.handleIMU();
        if(currentPitch < lastPitch - 10 || currentPitch > lastPitch + 10) currentPitch = lastPitch;
        if(currentPitch > -3) currentState = FIND_FRIAR;
        lastPitch = currentPitch;
        if (robot.checkRangefinder()) {
            distance = robot.checkRangefinder();
            robot.handleWallDistanceReading(distance, true);
        }
        break;
    case TURN_AROUND:  
        robot.setTargetTurnLocal(180);
        robot.handleUpdatePoint();
        if (robot.checkDestination()) currentState = FIND_FRIAR;
        break;
    case FIND_FRIAR:
        //Need new function and image controller for squaring up on friar laurence,
        if(friarLaurence.friarAddressed) currentState = KISS_ROMI;
        break;
    case KISS_ROMI:
    
    default:
        break;

  }

}