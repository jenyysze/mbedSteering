#include "CanThrottle.h"
#include <iostream> // TODO: remove

// Speed request: first char = 7
// Activate motor: first char = 8
// stop motor: first char = 9

const float startThreshold = 0.2; // TODO: implement this
const float lowScaleFactor = 0.3;
const float midScaleFactor = 0.6;
const float highScaleFactor = 1;

CanThrottle::CanThrottle(PinName throttlePin, unsigned canID, DigitalIn *rangePins_) : 
    CanAnalog(throttlePin, canID), 
    throttleRange(low),
    rangePins(rangePins_)
    {
        isActive = false;
    }

void CanThrottle::poll() { 
    updateConfiguration();
    if(isActive) {
        float dataAsFloat = read(); // Between 0 and 1
        // Must break out of each case, defualt behavior is to fallthrough
        // Scales data based on throttle ranges
        switch(throttleRange) {
            case low:
                dataAsFloat *= lowScaleFactor;
                break;
            case mid:
                dataAsFloat *= midScaleFactor;
                break;
            case high:
                dataAsFloat *= highScaleFactor;
                break;
        }

        char data[8]; 
        sprintf(data, "%c%.2f", '7', dataAsFloat);
        cout << data << endl;
        sendMessage(data);
    }
}

void CanThrottle::updateConfiguration() {
    if(rangePins[0].read()) {
        throttleRange = low;
    } else if(rangePins[1].read()) {
        throttleRange = mid;
    } else if(rangePins[2].read()) {
        throttleRange = high;
    }
}

void CanThrottle::activate() {
    if(!isActive) {
        cout << "Activating" << endl;
        sendMessage("8");
        isActive = true;
    }
}

// Continiously sends for safety
void CanThrottle::deactivate() {
    cout << "Deactivating" << endl;
    stopMotor();
    isActive = false;
}

void CanThrottle::stopMotor() {
    sendMessage("9");
}