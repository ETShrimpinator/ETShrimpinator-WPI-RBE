#pragma once
#include <Arduino.h>

class LED {
    
public:

    int ledPin = 0;
    void init (int);
    void pulse (int);
    void solidOn (void);
    void solidOff (void);

};