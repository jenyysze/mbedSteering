#include "CanThrottle.h"
#include <iostream> // TODO: remove

// Activate motor: data = 8
// stop motor: data = 9

const float lowScaleFactor = 0.3;
const float midScaleFactor = 0.6;
const float highScaleFactor = 1;

CanThrottle::CanThrottle(PinName throttlePin, unsigned canID, DigitalIn *rangePins_) : 
    CanAnalog(throttlePin, canID), 
    throttleRange(low),
    rangePins(rangePins_),
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
        sprintf(data, "%c%.2f", mode, dataAsFloat);
        cout << data << endl;
        sendMessage(data);
    }
}

// TODO: Find a better way to only check if it changed? (interupts with callback gave errors)
void CanThrottle::updateConfiguration() {
    if(rangePins[0].read() == 0) {
        throttleRange = low;
    } else if(rangePins[1].read() == 0) {
        throttleRange = mid;
    } else if(rangePins[2].read() == 0) {
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