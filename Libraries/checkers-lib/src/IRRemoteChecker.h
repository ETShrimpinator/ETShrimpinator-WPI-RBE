#pragma once

#include <IRDecoder.h>

class IRRemoteChecker {
    
    IRDecoder irDecoder;

public:

    void initializeIRRemote();
    int16_t checkIRPress();
    int16_t keyCode;

};