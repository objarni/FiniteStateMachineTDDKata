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


TEST_CASE( "ButtonFsmBehaviour")
{
    SECTION("initial state") {
        ButtonFsm fsm;
        initButtonFSM(&fsm);
        REQUIRE( fsm.state == State::waitForPress );
        SECTION("on press") {
            Signal publishSignal = buttonSignalHandler(&fsm, Signal::USER_PRESS);
            REQUIRE( fsm.state == State::waitForElevator );
            REQUIRE( publishSignal == Signal::LAMP_ON );
        }
        SECTION("elevator arrived") {
            fsm.state = State::waitForElevator;
            Signal publishSignal = buttonSignalHandler(&fsm, Signal::ELEVATOR_ARRIVED);
            REQUIRE( fsm.state == State::waitForPress );
            REQUIRE( publishSignal == Signal::LAMP_OFF );
        }
    }
}

