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
int runLoopSpeed = 100; //ms

void setup() {
    loopTimer.start();
}

int main() {
    setup();
    int prevLoopStartTime = loopTimer.read_ms();

    while(true) {
        while (loopTimer.read_ms() - prevLoopStartTime < runLoopSpeed) {} //Regulate speed of the main loop to runLoopSpeed
		prevLoopStartTime = loopTimer.read_ms();

        throttle.poll();
        updateMotorState();

        // Accessories
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

