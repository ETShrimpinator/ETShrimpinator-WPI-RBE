#include <IRPositionChecker.h>

void IRPositionChecker::initializeIRPosition() {

irPositionSensor.begin();

}

int16_t IRPositionChecker::checkIRPosition() {

  /*!
   *  @brief request the position
   */
  irPositionSensor.requestPosition();
  /*!
   *  @brief If there is data available, print it. Otherwise show the error message.
   */
  if (irPositionSensor.available()) {
    for (int i=0; i<4; i++) 
    {
      point = irPositionSensor.ReadPoint(i);
      //Serial.print(point.x);
      //Serial.print(",");
      
      //Serial.print(point.y);
      //Serial.print(";");

    }

    //Serial.print('\n');
    return point.x;

  }

  else Serial.println("Device not available!");

}