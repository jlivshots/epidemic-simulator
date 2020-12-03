#include <core/virus.h>

#include <catch2/catch.hpp>

TEST_CASE(
    "Verify constructor throws invalid argument exceptions for invalid "
    "infectiousness") {
  SECTION("Infectiousness less than 0 throws exception") {
    REQUIRE_THROWS_AS(epidemic_simulator::Virus(-0.0001, 2, 2),
                      std::invalid_argument);
  }

  SECTION("Infectiousness of 0 does not throw exception") {
    REQUIRE_NOTHROW(epidemic_simulator::Virus(0, 2, 2));
  }

  SECTION("Infectiousness between 0-1 does not throw exception") {
    REQUIRE_NOTHROW(epidemic_simulator::Virus(0.234, 2, 2));
  }

  SECTION("Infectiousness of 1 does not throw exception") {
    REQUIRE_NOTHROW(epidemic_simulator::Virus(1, 2, 2));
  }

  SECTION("Infectiousness of more than 1 throws exception") {
    REQUIRE_THROWS_AS(epidemic_simulator::Virus(1.001, 2, 2),
                      std::invalid_argument);
  }
}