#include "../mbed.h"
#include "../mbedCanLib/src/CanItem.h"
#include "../mbedCanLib/src/CanAnalog.h"
#include <vector>

#ifndef CANTHROTTLE_H
#define CANTHROTTLE_H 

// Defualt throttleMode: constantPower , Defualt throttleRange: low
class CanThrottle: private CanAnalog {
    public:
        enum ThrottleMode {constantVelocity = 0, constantPower = 1};
        enum ThrottleRange {low = 0, mid = 1, high = 2};
        CanThrottle(PinName throttlePin, unsigned canID, DigitalIn *rangePins_, DigitalIn *modePins_); 
        void poll(); // Override
        void activate();
        void deactivate();
    private:
        bool isActive;
        ThrottleMode throttleMode;
        ThrottleRange throttleRange;
        DigitalIn *rangePins; // [lo, mid, high]
        DigitalIn *modePins; // [constVel, constPow]
        void updateConfiguration();
        void stopMotor();
};

#endif 