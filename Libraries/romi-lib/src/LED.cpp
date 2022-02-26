#include <LED.h>

void LED::init(int pin) {
    
    pinMode(pin, OUTPUT);
    ledPin = pin;

}

void LED::pulse(int interval) { //interval in ms

    uint32_t time = millis();
    static uint32_t lastPulse = 0;

    if (time - lastPulse >= interval) {
        lastPulse = time;
        if (digitalRead(ledPin) == 1) digitalWrite(ledPin, LOW); 
        else if (digitalRead(ledPin) == 0) digitalWrite(ledPin, HIGH); 

    }

} 

void LED::solidOn(void) { digitalWrite(ledPin, HIGH); }
void LED::solidOff(void) { digitalWrite(ledPin, LOW); } 