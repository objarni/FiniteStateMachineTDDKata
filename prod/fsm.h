#pragma once

typedef enum {
    waitForPress, waitForElevator
} State;

typedef enum {
    USER_PRESS,
    DOORS_OPENING,
} Signal;

typedef struct {
    State state;
} ButtonFsm;

void initButtonFSM(ButtonFsm* fsm);

void buttonSignalHandler(
    ButtonFsm *fsm,
    Signal signal
);
