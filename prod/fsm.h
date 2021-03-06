//
// Created by ubuntu on 2021-03-03.
//

#ifndef FSM_PRACTICE_H
#define FSM_PRACTICE_H

typedef enum {
    waitForPress, waitForElevator
} State;

typedef enum {
    USER_PRESS,
    LAMP_ON,
    ELEVATOR_ARRIVED,
    LAMP_OFF
} Signal;

typedef struct {
    State state;
} ButtonFsm;

void initButtonFSM(ButtonFsm* fsm);

Signal buttonSignalHandler(
    ButtonFsm *fsm,
    Signal signal
);


#endif //FSM_PRACTICE_H
