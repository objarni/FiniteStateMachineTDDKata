#include <stdio.h>
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

Signal waitForPressHandler(ButtonFsm *fsm, Signal signal) {
    lampAPI(1);
}

Signal waitForElevetorHandler(ButtonFsm *fsm, Signal signal) {
    lampAPI(0);
}

typedef Signal (*Handler)(ButtonFsm *, Signal signal);

typedef struct {
    State inState;
    Signal onSignal;
    State toState;
    Handler handler;
} Transition;

Transition transitionTable[] = {
        {waitForPress,    USER_PRESS,       waitForElevator, waitForPressHandler},
        {waitForElevator, ELEVATOR_ARRIVED, waitForPress,    waitForElevetorHandler},
};

void buttonSignalHandler(ButtonFsm *fsm, Signal signal) {
    for (int i = 0; i < sizeof(transitionTable) / sizeof(Transition); i++) {
        Transition check = transitionTable[i];
        if (check.inState == fsm->state && check.onSignal == signal) {
            check.handler(fsm, signal);
            fsm->state = check.toState;
            return;
        }
    }
    return;
}

void setLampAPI(LampAPI newLampAPI) {
    lampAPI = newLampAPI;
}

// Wishlist
// 'meatier' state handlers e.g reading values or calling APIs
//  Idea: lamp could be API controlled instead of signal
// Publishing signals via API not return (realism)
// external state / separate type for FSM state
// Third state
//   Idea: introduce alarm end state

// Out of scope
// Data to signals
// Publish multiple signals
// Hierarchical state machine
