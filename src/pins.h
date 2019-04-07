#include "mbed.h"
#include "../mbedCanLib/src/CanButton.h"
#include "CanThrottle.h"
#include "../mbedCanLib/src/CanIDs.h"

#ifndef PINS_H
#define PINS_H

extern CAN can(p30, p29, 500000); // Actual pins
extern Serial pc(USBTX, USBRX); // To print to computer terminal, for testing

CanThrottle throttle(p20,throttleID); 

// CanItems
CanButton indicatorR(p6, indicatorRID);
CanButton indicatorL(p5, indicatorLID);
CanButton headlights(p8, headlightsID);
CanButton wiper(p9, wiperID); 
CanButton hazards(p10, hazardsID); 
CanButton horn(p24, hornID);
CanButton brakeLights(p25, brakeID); 

DigitalIn deadManSwitch(p21, PullDown);
#endif




