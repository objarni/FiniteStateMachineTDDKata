#include <iostream>

//#include <catch2/catch.hpp>
#include <gtest/gtest.h>

extern "C" {
#include "../prod/fsm.h"
}

TEST(ButtonFsm, 1)
{
    ButtonFsm fsm;
    initButtonFSM(&fsm);
    ASSERT_EQ(fsm.state, State::waitForPress);
}

TEST(ButtonFsm, 2) {
    ButtonFsm fsm;
    initButtonFSM(&fsm);
    buttonSignalHandler(&fsm, Signal::USER_PRESS);
    ASSERT_EQ(fsm.state, State::waitForElevator);
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

