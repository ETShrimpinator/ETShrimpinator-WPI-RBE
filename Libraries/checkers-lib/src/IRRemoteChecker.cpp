#include <IRRemoteChecker.h>

void IRRemoteChecker::initializeIRRemote() {

irDecoder.init();

}

int16_t IRRemoteChecker::checkIRPress() {

//check the IR remote
    keyCode = irDecoder.getKeyCode();
    if(keyCode != -1) return keyCode;
    else return -1;

}