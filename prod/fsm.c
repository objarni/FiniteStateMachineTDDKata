#include "fsm.h"
#include "port.h"

void initButtonFSM(ButtonFsm *fsm) {
    fsm->state = waitForPress;
}

void buttonSignalHandler(ButtonFsm *fsm, Signal signal) {
    switch (fsm->state) {
        case waitForPress:
            if (signal == USER_PRESS) {
                fsm->state = waitForElevator;
            }
            break;
        case waitForElevator:
            if (signal == DOORS_OPENING) {
                fsm->state = waitForPress;
            }
            break;
    }
}
