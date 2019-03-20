#include "../mbed.h"
#include "../mbedCanLib/src/CanItem.h"
#include "../mbedCanLib/src/CanAnalog.h"
#include <vector>

#ifndef CANTHROTTLE_H
#define CANTHROTTLE_H 

// Defualt throttleMode: constantPower , Defualt throttleRange: low
class CanThrottle: private CanAnalog {
    public:
        enum ThrottleRange {low = 0, mid = 1, high = 2};
        CanThrottle(PinName throttlePin, unsigned canID, DigitalIn *rangePins_); 
        void poll(); // Override
        void activate();
        void deactivate();
    private:
        bool isActive;
        ThrottleRange throttleRange;
        DigitalIn *rangePins; // [lo, mid, high]
        void updateConfiguration();
        void stopMotor();
};

#endif 