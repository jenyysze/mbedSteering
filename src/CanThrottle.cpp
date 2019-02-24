#include "CanThrottle.h"
#include <iostream> // TODO: remove

// Throttle data: first num -> mode, following are the data
// constantVolocity: mode = 0
// constantPower: mode = 1
// Activate motor: data = 8
// stop motor: data = 9

// TODO: Calibrate these
const float maxVelocity = 40000.0; // This can actually up to ~8000 (or more?)
const float maxCurrent = 20.0; // [A], this can go up to 75 actually (perhaps 150)
const float lowScaleFactor = 0.3;
const float midScaleFactor = 0.6;
const float highScaleFactor = 1;

CanThrottle::CanThrottle(PinName throttlePin, unsigned canID, DigitalIn *rangePins_, DigitalIn *modePins_) : 
    CanAnalog(throttlePin, canID), 
    throttleMode(constantPower),
    throttleRange(low),
    rangePins(rangePins_),
    modePins(modePins_) 
    {
        isActive = false;
    }

void CanThrottle::poll() { 
    updateConfiguration();
    if(isActive) {
        float dataAsFloat = read(); // Between 0 and 1
        char mode;

        // Must break out of each case, defualt behavior is to fallthrough
        switch(throttleMode) {
            case constantVelocity:
                dataAsFloat *= maxVelocity;
                mode = '0';
                break;
            case constantPower:
                dataAsFloat *= maxCurrent;
                mode = '1';
                break;
        }

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
        sprintf(data, "%c%.3f", mode, dataAsFloat);
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
    if(modePins[0].read() == 0) {
        throttleMode = constantVelocity;
    } else if(modePins[1].read() == 0) {
        throttleMode = constantPower;
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