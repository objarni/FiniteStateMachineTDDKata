#include "../prod/fsm.h"
#include "fsm.h"

/*
 * Building a button FSM using TDD
 * Behaviour of the button:
 * The button is an elevator button, with
 * a little lamp in it. The text "Hit"
 * is physically on the button, so that
 * when someone presses it, it lights up
 * indicating that the elevator is going
 * here. When the elevator arrives, the
 * lamp goes off again.
 *
 * Signals:
 *    - USER_PRESS when a press happens
 *    - DOORS_OPENING when elevator arrives (doors open then)
 * Guessed states:
 *    - waitingForPress
 *    - waitingForElevator
 *
 * We will see if we understand the problem better
 * and add/remove to these signals and states as we go along!
 *
 * I think that's enough 'specing' for now, lets' roll!
 */

void initButtonFSM(ButtonFsm *fsm) {
    fsm->state = waitForPress;
}

Signal doWaitForPress(ButtonFsm *fsm, Signal signal) {
    if (signal == USER_PRESS) {
        fsm->state = waitForElevator;
        return LAMP_ON;
    } else {
        return DO_NOT_PUBLISH;
    }
}

Signal doWaitForElevator(ButtonFsm *fsm, Signal signal) {
    if (signal == ELEVATOR_ARRIVED) {
        fsm->state = waitForPress;
        return LAMP_OFF;
    } else {
        return DO_NOT_PUBLISH;
    }
}

Signal buttonSignalHandler(ButtonFsm *fsm, Signal signal) {
    switch (fsm->state) {
        case waitForPress:
            return doWaitForPress(fsm, signal);
        case waitForElevator:
            return doWaitForElevator(fsm, signal);
    }
}
