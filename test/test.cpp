#include <iostream>

#include <catch2/catch.hpp>

/*
 * Test list
 * [x] starts in waitForPress state
 * [x] when in waitForPress state, a USER_PRESS signal
 *     gets us to waitForElevator state
 * [ ] when in waitForElevator state, a DOORS_OPENING
 *     signal transitions to waitingForPress state
 * [ ] other combinations result in no state change
 *     e.g waitForElevator getting USER_PRESS
 */

extern "C" {
#include "../prod/fsm.h"
}

TEST_CASE("ButtonFsmBehaviour")
{
    ButtonFsm fsm;
    initButtonFSM(&fsm);

    SECTION("when waiting for press") {
        REQUIRE(fsm.state == State::waitForPress);
        SECTION("and a press is seen") {
            buttonSignalHandler(&fsm, Signal::USER_PRESS);
            REQUIRE(fsm.state == State::waitForElevator);
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
        }
        SECTION("then pressing has no effect") {
            buttonSignalHandler(&fsm, Signal::USER_PRESS);
            REQUIRE(fsm.state == State::waitForElevator);
        }
    }
}

