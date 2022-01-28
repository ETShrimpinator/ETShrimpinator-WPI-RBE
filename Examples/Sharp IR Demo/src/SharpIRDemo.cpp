/*
 * Code for interfacing with the MCP3002 ADC using the SPI bus on the ESP32.
 * This code is written to use specific pins:
 * 
 * MISO = 19
 * MOSI = 23
 * SCLK = 18
 * SS   = 5
 * 
 * RX   = 16 (inverted for MaxBotix!)
 * (best not to use TX-17 for anything else, since the uart will likely conflict with pin operation)
 * 
 * pulse width is read on: 35
 * ultrasonic control pin: 2
 */

#include <Arduino.h>
#include <SPI.h>
#include <SharpIR.h>

SharpIR rangefinder (1,1);

void setup()
{

  delay(1000);
  
  Serial.begin(115200);
  Serial.println("Velkommen til");

  rangefinder.init(USE_CTRL_PIN);

}

void loop() 
{

        //passing true ignores the timer and forces a reading
    //from the datasheet, if the serial output is ready, the voltage is ready
    uint16_t adcReading = ultrasonic.readMCP3002(true);
    Serial.print(adcReading); 
    Serial.print('\t');
    Serial.print(0); //TODO: change this line to output distance in cm
    Serial.print('\n');

}
