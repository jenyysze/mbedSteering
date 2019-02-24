// IMPORTANT:
// * Need breakpoint on first line of main to debug without an exception, known error in VSCode
// * Do not use wait statements while debugging
// * For serial print use pc.print, and open "screen mbed sterm" in terminal
// * For some reason during debugging analog read is not working properly, so dont debug while testing throttle

#include "../mbed.h"
#include "Pins.h"
#include <iostream>

void updateMotorState();

Timer loopTimer;
// int runLoopSpeed = 10; //ms
int runLoopSpeed = 1000; //ms //TODO: remove, this is temp

void setup() {
    loopTimer.start();
}

int main() {
    setup();
    int prevLoopStartTime = loopTimer.read_ms();

    while(true) {
        while (loopTimer.read_ms() - prevLoopStartTime < runLoopSpeed) {} //Regulate speed of the main loop to runLoopSpeed
		prevLoopStartTime = loopTimer.read_ms();

        updateMotorState();
        throttle.poll();

        // Add every active can button here and call poll()
        // indicatorR.poll(); 
    }
}

void updateMotorState() {
    if(motorDeactivated) {
        throttle.deactivate();
    } else {
        throttle.activate();
    }
}

