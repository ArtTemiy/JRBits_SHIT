//
// Created by ArtTemiy on 22.06.2020.
//
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../Physics/double_i.h"

unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}

TEST_CASE("Factorials are computed", "[factorial]") {
    REQUIRE(double_i() == double_i());
    REQUIRE(double_i() == 0);
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    REQUIRE( Factorial(10) == 3628800 );
}
