#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

#include "main.cpp"

TEST_CASE("Prime Number", "[prime number]")
{
    auto first = PrimeNumbersRange<short>{ 1, 10 };
    REQUIRE( first[0] == 1 );
}
