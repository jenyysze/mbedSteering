#include "CanThrottle.h"
#include <iostream> // TODO: remove

// TODO: Calibrate these
const float maxVelocity = 4000.0; // This can actually up to ~8000
const float maxCurrent = 10.0; // [A], this can go up to 75 actually (perhaps 150)
const float lowScaleFactor = 0.3;
const float midScaleFactor = 0.6;
const float highScaleFactor = 1;

CanThrottle::CanThrottle(PinName throttlePin, unsigned canID_, DigitalIn *rangePins_, DigitalIn *modePins_) : 
    CanItem(canID_), 
    throttle(throttlePin),
    throttleMode(constantPower),
    throttleRange(low),
    rangePins(rangePins_),
    modePins(modePins_) 
    {}

// Throttle data: first num -> mode, following are the data
// constantVolocity: mode = 0
// constantPower: mode = 1
// stop motor: data = 0000

void CanThrottle::poll() { 
    updateConfiguration();
    float dataAsFloat = throttle.read(); // Between 0 and 1
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


    char data[10]; 
    sprintf(data, "%c%.3f", mode, dataAsFloat);
    sendMessage(data);
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

void CanThrottle::stopMotor() {
    sendMessage("0000");
}
