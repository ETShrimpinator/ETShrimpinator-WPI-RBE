#include <IREmitter.h>
#include <ESP32Tone.h>

void IREmitter::init(int pin)
{
    
    pinMode(pin, OUTPUT);
    emitterPin = pin;

}

void IREmitter::pulse(int frequency) //Frequency in hz
{

   tone(emitterPin, frequency);

}

void IREmitter::solidOn(void) {

    digitalWrite(emitterPin, HIGH); 

}

void IREmitter::solidOff(void) {

    digitalWrite(emitterPin, LOW); 

}