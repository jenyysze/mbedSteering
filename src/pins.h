#include "mbed.h"
#include "../mbedCanLib/src/CanButton.h"
#include "CanThrottle.h"
#include "../mbedCanLib/src/CanIDs.h"

#ifndef PINS_H
#define PINS_H

extern CAN can(p30, p29, 500000); // Actual pins
extern Serial pc(USBTX, USBRX); // To print to computer terminal, for testing

// Dials for throttle controls
DigitalIn loRangePin(p15, PullDown); // dial1
DigitalIn midRangePin(p16, PullDown); //dial2
DigitalIn highRangePin(p17, PullDown); //dial3

DigitalIn rangePins[] = {loRangePin, midRangePin, highRangePin}; // [lo, mid, high]
CanThrottle throttle(p20,throttleID, rangePins); 

// CanItems
CanButton indicatorR(p5, indicatorRID);
CanButton indicatorL(p6, indicatorLID);
CanButton headlights(p8, headlightsID);
CanButton wiper(p9, wiperID); // Comment this out for testing (w/ current wiring)
CanButton hazards(p10, hazardsID); // Comment this out for testing (w/ current wiring)
CanButton horn(p24, hornID);

// TODO: Add screen pins
DigitalIn motorActivated(p7, PullDown);
DigitalIn deadManSwitch(p21, PullDown);

#endif




