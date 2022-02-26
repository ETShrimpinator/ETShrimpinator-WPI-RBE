#include <FriarLaurence.h>
#include <MQTT.h>

void FriarLaurence::init() {

robot.init(enableLED, enableIREmitter, enableRangefinder, enableIMU, enableIRPositionSensor);

}

void FriarLaurence::runStateMachine() {

    client.publish("team20/friarAddressed", String(friarAddressed).c_str());

switch(currentState) {

    case IDLE:
        break;
    case ADDRESSJULIET:
        break;
    case ADDRESSROMI:
        break;
    default:
        break;

}

}