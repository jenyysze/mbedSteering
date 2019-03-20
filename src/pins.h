#include "mbed.h"
#include "../mbedCanLib/src/CanButton.h"
#include "CanThrottle.h"
#include "../mbedCanLib/src/CanIDs.h"

#ifndef PINS_H
#define PINS_H

extern CAN can(p30, p29,1000000); // Actual pins
// extern CAN can(p9, p10, 1000000); // Use for testing (current wiring)
extern Serial pc(USBTX, USBRX); // To print to computer terminal, for testing

// Dials for throttle controls
DigitalIn loRangePin(p15, PullDown); // dial1
DigitalIn midRangePin(p16, PullDown); //dial2
DigitalIn highRangePin(p17, PullDown); //dial3

// Unused dial inputs
DigitalIn dial4(p18, PullDown); //dial4
DigitalIn dial5(p19, PullDown); //dial5

DigitalIn rangePins[] = {loRangePin, midRangePin, highRangePin}; // [lo, mid, high]
CanThrottle throttle(p20,throttleID, rangePins, modePins); 

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

//Serial serial(p28,p27); // For communication with motor controller over UART (TX, RX)

#endif




