#include <iostream>

#include <gtest/gtest.h>

extern "C" {
#include "../prod/fsm.h"
#include "../prod/port.h"
}

unsigned char fakePorts[4] = {0, 0, 0, 0};

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

TEST(ButtonFsm, lampGoesOnWhenUserPressesButton) {
    ButtonFsm fsm;
    initButtonFSM(&fsm);
    setPortAddress0(&fakePorts[0]);
    buttonSignalHandler(&fsm, Signal::USER_PRESS);
    unsigned char got = int(fakePorts[1]);
    unsigned char want = 1 << 7;
    ASSERT_EQ(got, want);
}

TEST(ButtonFsm, lampGoesOffWhenUserPressesButton) {
    ButtonFsm fsm;
    initButtonFSM(&fsm);
    fsm.state = State::waitForElevator;
    fakePorts[1] = 255; // Set all bits
    setPortAddress0(&fakePorts[0]);
    buttonSignalHandler(&fsm, Signal::DOORS_OPENING);
    unsigned char got = int(fakePorts[1]);
    unsigned char want = 0b01111111; // Expect bit to have been cleared
    ASSERT_EQ(got, want);
}

TEST(ButtonFsm, doesNotTouchOtherBitsOnLampOn) {
    ButtonFsm fsm;
    initButtonFSM(&fsm);
    setPortAddress0(&fakePorts[0]);
    fakePorts[1] = 0b11111111;
    buttonSignalHandler(&fsm, Signal::USER_PRESS);
    unsigned char got = int(fakePorts[1]);
    unsigned char want = 0b11111111;
    ASSERT_EQ(got, want);
}

/*
 * Test list / scratch notes
 * [x] starts in waitForPress state
 * [x] when in waitForPress state, a USER_PRESS signal
 *     gets us to waitForElevator state
 * [x] when in waitForElevator state, a DOORS_OPENING
 *     signal transitions to waitingForPress state
 * Other combinations should result in no state change
 * [x] waitForElevator getting USER_PRESS or
 * [x] waitForPress getting DOORS_OPENING
 * [ ] when going to waitForElevator state, the lamp is
 *     turned on. The lamp is turned on by setting bit 7 of port 1
 * [ ] when going to waitForPress state, the lamp is
 *     turned off. The lamp is turned off by clearing bit 7 of port 1
 * [ ] the button fsm should not modify any other bit of port 1
 *     (or any other of the 4 ports)
 */

