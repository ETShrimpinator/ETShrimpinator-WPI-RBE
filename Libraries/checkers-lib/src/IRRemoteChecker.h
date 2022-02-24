#include <IRDecoder.h>

class IRRemoteChecker {
    
    IRDecoder irDecoder;

public:

    int16_t checkIRPress();
    int16_t keyCode;

};