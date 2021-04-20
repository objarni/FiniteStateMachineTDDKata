#include "fsm.h"
#include "port.h"

void initButtonFSM(ButtonFsm *fsm) {
    fsm->state = waitForPress;
}

void buttonSignalHandler(ButtonFsm *fsm, Signal signal) {
    unsigned char *port1 = getPortAddress(1);
    switch (fsm->state) {
        case waitForPress:
            if (signal == USER_PRESS) {
                *port1 &= 1 << 7;
                fsm->state = waitForElevator;
            }
            break;
        case waitForElevator:
            if (signal == DOORS_OPENING) {
                *port1 ^= 1 << 7; // clear bit 7
                fsm->state = waitForPress;
            }
            break;
    }
}
