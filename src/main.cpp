// IMPORTANT:
// * Need breakpoint on first line of main to debug without an exception, known error in VSCode
// * Do not use wait statements while debugging
// * For serial print use "mbed sterm" in terminal
// * For some reason during debugging analog read is not working properly, so dont debug while testing throttle

#include "../mbed.h"
#include "Pins.h"
#include <iostream>

void updateMotorState();

Timer loopTimer;
int runLoopSpeed = 200; //ms

void setup() {
    loopTimer.start();
}

int main() {
    setup();
    int prevLoopStartTime = loopTimer.read_ms();

    while(true) {
        // Throttle
        while (loopTimer.read_ms() - prevLoopStartTime < runLoopSpeed / 2) {} //Regulate speed of the main loop throttle delay
        prevLoopStartTime = loopTimer.read_ms();
        updateMotorState();
        throttle.poll();

        // Accessories
        while (loopTimer.read_ms() - prevLoopStartTime < runLoopSpeed / 2) {} //Regulate speed of the main loop, accessories delay
		prevLoopStartTime = loopTimer.read_ms();
        indicatorR.poll(); 
        indicatorL.poll(); 
        headlights.poll();
        wiper.poll();
        hazards.poll();
        horn.poll();
        brakeLights.poll();
    }
}

void updateMotorState() {
    if(!motorActivated.read() || !deadManSwitch.read()) { 
        throttle.deactivate();
    } else {
        throttle.activate();
    }
}

