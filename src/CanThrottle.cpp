#include "CanThrottle.h"
#include <iostream> // TODO: remove

// Speed request: first char = 7
// Activate motor: first char = 8
// stop motor: first char = 9

const float startThreshold = 0.2; // TODO: implement this
const float throttleScaleFactor = 1; // TODO: tune

CanThrottle::CanThrottle(PinName throttlePin, unsigned canID) : CanAnalog(throttlePin, canID), isActive(false) {}

void CanThrottle::poll() { 
    if(isActive) {
        float dataAsFloat = read(); // Between 0 and 1
        dataAsFloat *= throttleScaleFactor;
        char data[8]; 
        sprintf(data, "%c%.2f", '7', dataAsFloat);
        //cout << data << endl;
        sendMessage(data);
    }
}

void CanThrottle::activate() {
    if(!isActive) {
        //cout << "Activating" << endl;
        sendMessage("8");
        isActive = true;
    }
}

// Continiously sends for safety
void CanThrottle::deactivate() {
    //cout << "Deactivating" << endl;
    stopMotor();
    isActive = false;
}

void CanThrottle::stopMotor() {
    sendMessage("9");
}