#include <iostream>

#include <gtest/gtest.h>

extern "C" {
#include "../prod/fsm.h"
}

TEST(ButtonFsm, initialState)
{
    ButtonFsm fsm;
    initButtonFSM(&fsm);
    ASSERT_EQ(fsm.state, State::waitForPress);
}

TEST(ButtonFsm, userPressesButton) {
    ButtonFsm fsm;
    initButtonFSM(&fsm);
    buttonSignalHandler(&fsm, Signal::USER_PRESS);
    ASSERT_EQ(fsm.state, State::waitForElevator);
}

TEST(ButtonFsm, elevatorArrive) {
    ButtonFsm fsm;
    initButtonFSM(&fsm);
    fsm.state = State::waitForElevator;
    buttonSignalHandler(&fsm, Signal::DOORS_OPENING);
    ASSERT_EQ(fsm.state, State::waitForPress);
}

TEST(ButtonFsm, pressingButtonWhenWaitingForElevator) {
    ButtonFsm fsm;
    initButtonFSM(&fsm);
    fsm.state = State::waitForElevator;
    buttonSignalHandler(&fsm, Signal::USER_PRESS);
    ASSERT_EQ(fsm.state, State::waitForElevator);
}

TEST(ButtonFsm, elevatorArrivingWhenWaitingForPress) {
    ButtonFsm fsm;
    initButtonFSM(&fsm);
    fsm.state = State::waitForPress;
    buttonSignalHandler(&fsm, Signal::DOORS_OPENING);
    ASSERT_EQ(fsm.state, State::waitForPress);
}

/*
 * Test list / scratch notes
 * [x] starts in waitForPress state
 * [x] when in waitForPress state, a USER_PRESS signal
 *     gets us to waitForElevator state
 * [ ] when in waitForElevator state, a DOORS_OPENING
 *     signal transitions to waitingForPress state
 * Other combinations should result in no state change
 * [ ] waitForElevator getting USER_PRESS or
 * [ ] waitForPress getting DOORS_OPENING
 */

