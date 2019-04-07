#include "CanThrottle.h"
#include <iostream> // TODO: remove

// Speed request: first char = 7
// Activate motor: first char = 8
// stop motor: first char = 9

const float startThreshold = 0.15; // TODO: fine tune
const float throttleScaleFactor = 6.6; // TODO: tune
const float maxThrottle = 1.0;

CanThrottle::CanThrottle(PinName throttlePin, unsigned canID) : CanAnalog(throttlePin, canID), isActive(false) {}

void CanThrottle::poll() {
    if(isActive) {
        float dataAsFloat = adjustedData(read()); // Between 0 and 1
        // cout << "float: " << dataAsFloat << endl;
        char data[8];   
        sprintf(data, "%c%.2f", '7', dataAsFloat);
        // cout << data << endl;
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
    // cout << "Stopping" << endl;
    sendMessage("9");
}

float CanThrottle::adjustedData(float data) {
    float adjustedData = (data - startThreshold);
    if(adjustedData < 0.0 || adjustedData > maxThrottle) {
        adjustedData = 0.0;
    }
    adjustedData *= throttleScaleFactor;
    return adjustedData;
}
