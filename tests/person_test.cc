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

  SECTION(
      "MoveTowardLocation() returns false when person hasn't yet reached "
      "target") {
    REQUIRE_FALSE(person.MoveTowardLocation(glm::vec2(4, -3.2), 3));
  }

  SECTION(
      "MoveTowardLocation() returns true when person moves 1 frame to end "
      "exactly on target") {
    REQUIRE(person.MoveTowardLocation(glm::vec2(-20, 21), 29));
  }

  SECTION(
      "MoveTowardLocation() returns true when person is less than 1 frame from "
      "target position") {
    REQUIRE(person.MoveTowardLocation(glm::vec2(-12.3, 1), 40));
  }
}

TEST_CASE("Verify Infect() correctness") {
  epidemic_simulator::Person person(glm::vec2(2, 2));

  SECTION(
      "Vulnerable person becomes incubating when incubation period is "
      "positive") {
    person.Infect(epidemic_simulator::Virus(1, 2, 2));
    REQUIRE(person.GetStatus() == epidemic_simulator::Status::Incubating);
  }

  SECTION(
      "Vulnerable person becomes infectious when incubation period is "
      "zero") {
    person.Infect(epidemic_simulator::Virus(1, 0, 2));
    REQUIRE(person.GetStatus() == epidemic_simulator::Status::Infectious);
  }
}