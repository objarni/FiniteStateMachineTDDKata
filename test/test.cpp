#include <iostream>

#include <catch2/catch.hpp>

/*
 * Test list
 * [x] starts in waitForPress state
 * [ ] when in waitForPress state, a USER_PRESS signal
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
    // A: These statements are run before any SECTION
    ButtonFsm fsm;
    initButtonFSM(&fsm);

    SECTION("1") {
        REQUIRE(fsm.state == State::waitForPress);
    }

    SECTION("2") {
        fsm.state = State::waitForPress; // B: This statement is run after A

        SECTION("2.1") {
            // C: This statement is run after A and B
            buttonSignalHandler(&fsm, Signal::USER_PRESS);
            REQUIRE(fsm.state == State::waitForElevator);
        }
    }
}

