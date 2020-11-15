#include <core/simulator.h>

#include <catch2/catch.hpp>

TEST_CASE("Verify constructor assigns slots evenly around the arena") {
  SECTION("No people in the arena") {
    epidemic_simulator::Simulator simulator(0, 20, 0);
    REQUIRE(simulator.GetPeople().empty());
    REQUIRE(simulator.GetSlots().empty());
  }

  SECTION("1 person in the arena") {
    epidemic_simulator::Simulator simulator(1, 2, 0);
    const std::vector<epidemic_simulator::Person>& people =
        simulator.GetPeople();
    const std::vector<glm::vec2>& slots = simulator.GetSlots();

    REQUIRE(people.size() == 1);
    REQUIRE(people[0].GetLocation() == glm::vec2(2, 0));

    REQUIRE(slots.size() == 1);
    REQUIRE(slots[0] == glm::vec2(2, 0));
  }

  SECTION("Multiple people in the arena") {
    epidemic_simulator::Simulator simulator(20, 100, 0);
    const std::vector<epidemic_simulator::Person>& people =
        simulator.GetPeople();
    const std::vector<glm::vec2>& slots = simulator.GetSlots();

    REQUIRE(people.size() == 20);
    REQUIRE(slots.size() == 20);
    for (size_t i = 0; i < 20; ++i) {
      REQUIRE(people[i].GetLocation() == slots[i]);
      REQUIRE(slots[i].x == Approx(100 * cos(2 * i * M_PI / 20)).epsilon(0.01));
      REQUIRE(slots[i].y == Approx(100 * sin(2 * i * M_PI / 20)).epsilon(0.01));
    }
  }
}

TEST_CASE("Shuffle Locations generates a valid permutation of slots") {
  SECTION("Empty arena") {
    epidemic_simulator::Simulator simulator(0, 100, 0);
    simulator.ShuffleSlots();
    REQUIRE(simulator.GetSlots().empty());
  }

  SECTION("Arena with 1 person") {
    epidemic_simulator::Simulator simulator(1, 100, 0);
    simulator.ShuffleSlots();
    const std::vector<glm::vec2>& slots = simulator.GetSlots();
    REQUIRE(slots.size() == 1);
    REQUIRE(slots[0] == glm::vec2(100, 0));
  }

  SECTION("Arena with many people") {
    epidemic_simulator::Simulator simulator(43, 100, 0);
    const std::vector<glm::vec2>& initial_slots = simulator.GetSlots();
    simulator.ShuffleSlots();
    const std::vector<glm::vec2>& shuffled_slots = simulator.GetSlots();
    REQUIRE(initial_slots.size() == 43);
    REQUIRE(shuffled_slots.size() == 43);

    for (const glm::vec2& slot : shuffled_slots) {
      REQUIRE(std::find(initial_slots.begin(), initial_slots.end(), slot) !=
              initial_slots.end());
    }
    for (const glm::vec2& slot : initial_slots) {
      REQUIRE(std::find(shuffled_slots.begin(), shuffled_slots.end(), slot) !=
              shuffled_slots.end());
    }
  }
}

TEST_CASE("Verify ApproachNewLocations() functionality") {
  SECTION("Method returns true immediately for 0-person arena") {
    epidemic_simulator::Simulator simulator(0, 100, 3);
    simulator.ShuffleSlots();
    REQUIRE(simulator.ApproachNewLocations());
  }
  SECTION("Method returns true for 1-person arena") {
    epidemic_simulator::Simulator simulator(1, 100, 3);
    simulator.ShuffleSlots();
    REQUIRE(simulator.ApproachNewLocations());
  }

  SECTION(
      "Method returns false until all people are at their new location for"
      "many-person arena") {
    epidemic_simulator::Simulator simulator(12, 100, 3);
    simulator.ShuffleSlots();
    while (!simulator.ApproachNewLocations()) {
      bool all_have_arrived = true;
      const std::vector<epidemic_simulator::Person>& people =
          simulator.GetPeople();
      const std::vector<glm::vec2>& slots = simulator.GetSlots();
      for (size_t i = 0; i < people.size(); ++i) {
        if (people[i].GetLocation() != slots[i]) {
          all_have_arrived = false;
        }
      }
      REQUIRE_FALSE(all_have_arrived);
    }
  }

  SECTION(
      "Method returns true once all people are at their new location for "
      "many-person arena") {
    epidemic_simulator::Simulator simulator(12, 100, 3);
    simulator.ShuffleSlots();
    while (!simulator.ApproachNewLocations()) {
    }
    const std::vector<epidemic_simulator::Person>& people =
        simulator.GetPeople();
    const std::vector<glm::vec2>& slots = simulator.GetSlots();

    for (size_t i = 0; i < people.size(); ++i) {
      REQUIRE(people[i].GetLocation() == slots[i]);
    }
  }
}