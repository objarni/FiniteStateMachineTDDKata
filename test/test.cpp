#include <iostream>

#include <catch2/catch.hpp>

/*
 * Test list
 * [x] starts in waitForPress state
 * [x] when in waitForPress state, a USER_PRESS signal
 *     gets us to waitForElevator state, and the lamp
 *     is turned on
 * [ ] when in waitForElevator state, a DOORS_OPENING
 *     signal transitions to waitingForPress state, and
 *     lamp is turned off (how?)
 *
 */

extern "C" {
#include "../prod/fsm.h"
}

bool lampOn = false;

TEST_CASE("ButtonFsmBehaviour")
{
    ButtonFsm fsm;
    initButtonFSM(&fsm);
    auto lampAPIFake = [](int setLampOn) { lampOn = setLampOn; };
    setLampAPI(lampAPIFake);

    SECTION("when waiting for press") {
        REQUIRE(fsm.state == State::waitForPress);
        SECTION("and a press is seen") {
            buttonSignalHandler(&fsm, Signal::USER_PRESS);
            REQUIRE(fsm.state == State::waitForElevator);
            REQUIRE(lampOn);
        }
        SECTION("and an elevator arrives") {
            buttonSignalHandler(&fsm, Signal::ELEVATOR_ARRIVED);
            REQUIRE(fsm.state == State::waitForPress);
        }
    }

    SECTION("when waiting for elevator") {
        fsm.state = State::waitForElevator;
        SECTION("and it arrives") {
            buttonSignalHandler(&fsm, Signal::ELEVATOR_ARRIVED);
            REQUIRE(fsm.state == State::waitForPress);
            REQUIRE(!lampOn);
        }
        SECTION("then pressing has no effect") {
            buttonSignalHandler(&fsm, Signal::USER_PRESS);
            REQUIRE(fsm.state == State::waitForElevator);
        }
    }
}

