#include "fsm.h"

void initButtonFSM(ButtonFsm *fsm) {
    fsm->state = waitForPress;
}

void buttonSignalHandler(ButtonFsm *fsm, Signal signal) {
    fsm->state = waitForElevator;
}
