#include <FriarLaurence.h>

void FriarLaurence::init() {

robot.init(enableLED, enableIREmitter, enableRangefinder, enableIMU, enableIRPositionSensor);

}

void FriarLaurence::runStateMachine() {

    client.publish("team20/friarAddressed", String(robot.friarAddressed).c_str());

switch(currentState) {

    case IDLE:
        robot.stop(); //Directly sets chassis wheel speeds to 0 
        if (coupleReady == true) currentState = ADDRESSJULIET;
        break;
    case ADDRESSJULIET:
        robot.setDestination(-3, 3);   //change with turn in place
        if (robot.checkChassis()) robot.handleUpdatePoint();
        if (robot.checkDestination()) currentState = ADDRESSROMI;
        break;
    case ADDRESSROMI:
        robot.setDestination(0, 6);
        if (robot.checkChassis()) robot.handleUpdatePoint();
        if (robot.checkDestination()) currentState = IDLE;
        break;
    default:
        break;

}