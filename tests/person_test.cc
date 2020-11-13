#include <core/person.h>

#include <catch2/catch.hpp>

TEST_CASE("Verify MoveTowardLocation() correctness") {
  epidemic_simulator::Person person(glm::vec2(0, 0));

  SECTION(
      "Person moves toward location by correct distance when farther than 1 "
      "frame away") {
    person.MoveTowardLocation(glm::vec2(90, 120), 5);
    REQUIRE(person.GetLocation() == glm::vec2(3, 4));
  }

  SECTION("Person moves to target location when exactly 1 frame away") {
    person.MoveTowardLocation(glm::vec2(-1, 0), 1);
    REQUIRE(person.GetLocation() == glm::vec2(-1, 0));
  }

  SECTION("Person moves to target location when less than 1 frame away") {
    person.MoveTowardLocation(glm::vec2(4, -3.2), 20);
    REQUIRE(person.GetLocation() == glm::vec2(4, -3.2));
  }

  SECTION("Person stays at target location once it's been reached") {
    person.MoveTowardLocation(glm::vec2(4, -3.2), 3);
    person.MoveTowardLocation(glm::vec2(4, -3.2), 3);
    REQUIRE(person.GetLocation() == glm::vec2(4, -3.2));
    person.MoveTowardLocation(glm::vec2(4, -3.2), 3);
    REQUIRE(person.GetLocation() == glm::vec2(4, -3.2));
  }


}