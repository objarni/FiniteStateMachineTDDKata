#include <stdio.h>
#include "../prod/fsm.h"
#include "fsm.h"

void initButtonFSM(ButtonFsm *fsm) {
    fsm->state = waitForPress;
}

void waitForPressHandler(ButtonFsm *fsm, Signal signal) {
}

void waitForElevetorHandler(ButtonFsm *fsm, Signal signal) {
}

typedef void (*Handler)(ButtonFsm *, Signal signal);

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
}
