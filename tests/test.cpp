#define CATCH_CONFIG_MAIN

#include <catch2/catch_test_macros.hpp>
#include <iostream>

TEST_CASE("Santiy Check", "[flag]") { REQUIRE(1 == 1); }

TEST_CASE("Asteroid Position", "[flag]") { REQUIRE(1 == 2); }
