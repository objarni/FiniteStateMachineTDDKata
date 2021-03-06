#include <iostream>

#include <catch2/catch.hpp>

extern "C" {
    #include "../prod/fsm.h"
}

TEST_CASE( "Suite", "test" ) {
    REQUIRE( fn(1) == 1 );
}
