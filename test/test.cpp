#include <iostream>

#include <gtest/gtest.h>

extern "C" {
#include "../prod/fsm.h"
#include "../prod/port.h"
}

unsigned char fakePorts[4] = {0, 0, 0, 0};

/* Test list 2
 * LAMP CONTROL
 * [ ] when going to waitForElevator state, the lamp is
 *     turned on. The lamp is turned on by setting bit 7 of port 1
 * [ ] when going to waitForPress state, the lamp is
 *     turned off. The lamp is turned off by clearing bit 7 of port 1
 * [ ] the button fsm should not modify any other bit of port 1
 *     (or any other of the 4 ports)
 */


TEST(ButtonFsm, initialState)
{
    ButtonFsm fsm;
    setPortAddress0(&fakePorts[0]);
    initButtonFSM(&fsm);
    setPortAddress0(&fakePorts[0]);
    ASSERT_EQ(fsm.state, State::waitForPress);
}

TEST(ButtonFsm, userPressesButton) {
    ButtonFsm fsm;
    initButtonFSM(&fsm);
    setPortAddress0(&fakePorts[0]);
    buttonSignalHandler(&fsm, Signal::USER_PRESS);
    ASSERT_EQ(fsm.state, State::waitForElevator);
}

TEST(ButtonFsm, elevatorArrive) {
    ButtonFsm fsm;
    fsm.state = State::waitForElevator;
    setPortAddress0(&fakePorts[0]);
    buttonSignalHandler(&fsm, Signal::DOORS_OPENING);
    ASSERT_EQ(fsm.state, State::waitForPress);
}

TEST(ButtonFsm, pressingButtonWhenWaitingForElevator) {
    ButtonFsm fsm;
    fsm.state = State::waitForElevator;
    setPortAddress0(&fakePorts[0]);
    buttonSignalHandler(&fsm, Signal::USER_PRESS);
    ASSERT_EQ(fsm.state, State::waitForElevator);
}

TEST(ButtonFsm, elevatorArrivingWhenWaitingForPress) {
    ButtonFsm fsm;
    fsm.state = State::waitForPress;
    setPortAddress0(&fakePorts[0]);
    buttonSignalHandler(&fsm, Signal::DOORS_OPENING);
    ASSERT_EQ(fsm.state, State::waitForPress);
}

/* Test list 1
 * STATE - SIGNAL - TRANSITION
 * [x] starts in waitForPress state
 * [x] when in waitForPress state, a USER_PRESS signal
 *     gets us to waitForElevator state
 * [x] when in waitForElevator state, a DOORS_OPENING
 *     signal transitions to waitingForPress state
 * Other combinations should result in no state change
 * [x] waitForElevator getting USER_PRESS or
 * [x] waitForPress getting DOORS_OPENING
 */
