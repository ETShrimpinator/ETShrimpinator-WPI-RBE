#pragma once
#include <Arduino.h>

class LED {

private:

public:

    int ledPin = 0;
    void init (int);
    void pulse (int);
    void solidOn (void);
    void solidOff (void);

};