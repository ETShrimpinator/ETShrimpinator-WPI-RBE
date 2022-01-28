#pragma once
#include <Arduino.h>


class IREmitter {

private:

public:

    int emitterPin = 0;
    void init (int);
    void pulse (int);
    void solidOn (void);
    void solidOff (void);

};
