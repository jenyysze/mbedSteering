#include "../mbed.h"
#include "../mbedCanLib/src/CanItem.h"
#include "../mbedCanLib/src/CanAnalog.h"
#include <vector>

#ifndef CANTHROTTLE_H
#define CANTHROTTLE_H 

// Defualt throttleMode: constantPower , Defualt throttleRange: low
class CanThrottle: private CanAnalog {
    public:
        CanThrottle(PinName throttlePin, unsigned canID); 
        void poll(); // Override
        void activate();
        void deactivate();
    private:
        bool isActive;
        void stopMotor();
};

#endif 