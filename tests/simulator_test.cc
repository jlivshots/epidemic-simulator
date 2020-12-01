#include <core/simulator.h>

#include <catch2/catch.hpp>

TEST_CASE("Verify constructor works as intended") {
  SECTION("No people in the arena") {
    epidemic_simulator::Simulator simulator(
        0, 20, 0, epidemic_simulator::Virus(1, 2, 2), 0, 0, 1, 1);
    REQUIRE(simulator.GetPeople().empty());
    REQUIRE(simulator.GetSlots().empty());
  }

  SECTION("People spaced evenly for 1 person in the arena") {
    epidemic_simulator::Simulator simulator(
        1, 2, 0, epidemic_simulator::Virus(1, 2, 2), 0, 0, 1, 1);
    const std::vector<epidemic_simulator::Person>& people =
        simulator.GetPeople();
    const std::vector<glm::vec2>& slots = simulator.GetSlots();

    REQUIRE(people.size() == 1);
    REQUIRE(people[0].GetLocation() == glm::vec2(2, 0));

    REQUIRE(slots.size() == 1);
    REQUIRE(slots[0] == glm::vec2(2, 0));
  }

  SECTION("People spaced evenly when multiple people in the arena") {
    epidemic_simulator::Simulator simulator(
        20, 100, 0, epidemic_simulator::Virus(1, 2, 2), 0, 0, 1, 1);
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

  SECTION("Exactly 1 person is infected for 1 person in arena") {
    epidemic_simulator::Simulator simulator(
        1, 2, 0, epidemic_simulator::Virus(1, 2, 2), 0, 0, 1, 1);
    const std::vector<epidemic_simulator::Person>& people =
        simulator.GetPeople();

    REQUIRE(people[0].GetStatus() == epidemic_simulator::Status::Incubating);
  }

  SECTION("Exactly 1 person is infected for multiple people in arena") {
    epidemic_simulator::Simulator simulator(
        14, 2, 0, epidemic_simulator::Virus(1, 2, 2), 0, 0, 1, 1);
    const std::vector<epidemic_simulator::Person>& people =
        simulator.GetPeople();
    for (size_t i = 0; i < people.size(); ++i) {
      if (i == 0) {
        REQUIRE(people[i].GetStatus() ==
                epidemic_simulator::Status::Incubating);
      } else {
        REQUIRE(people[i].GetStatus() ==
                epidemic_simulator::Status::Vulnerable);
      }
    }
  }
}

TEST_CASE("Shuffle People generates a valid permutation of slots") {
  SECTION("Empty arena") {
    epidemic_simulator::Simulator simulator(
        0, 100, 0, epidemic_simulator::Virus(1, 2, 2), 0, 0, 1, 1);
    simulator.ShufflePeople();
    REQUIRE(simulator.GetSlots().empty());
    REQUIRE(simulator.GetPeople().empty());
  }

  SECTION("Arena with 1 person") {
    epidemic_simulator::Simulator simulator(
        1, 100, 0, epidemic_simulator::Virus(1, 2, 2), 0, 0, 1, 1);
    simulator.ShufflePeople();
    const std::vector<epidemic_simulator::Person>& people =
        simulator.GetPeople();
    REQUIRE(people.size() == 1);
    REQUIRE(people[0].GetLocation() == glm::vec2(100, 0));
  }

  SECTION("Arena with many people") {
    epidemic_simulator::Simulator simulator(
        43, 100, 0, epidemic_simulator::Virus(1, 2, 2), 0, 0, 1, 1);
    const std::vector<epidemic_simulator::Person>& initial_people =
        simulator.GetPeople();
    simulator.ShufflePeople();
    const std::vector<epidemic_simulator::Person>& shuffled_people =
        simulator.GetPeople();
    REQUIRE(initial_people.size() == 43);
    REQUIRE(shuffled_people.size() == 43);

    for (const epidemic_simulator::Person& person : shuffled_people) {
      bool contained_in_initial = false;
      for (const epidemic_simulator::Person& other_person : initial_people) {
        if (other_person.GetLocation() == person.GetLocation()) {
          contained_in_initial = true;
          break;
        }
      }
      REQUIRE(contained_in_initial);
    }

    for (const epidemic_simulator::Person& person : initial_people) {
      bool contained_in_shuffled = false;
      for (const epidemic_simulator::Person& other_person : shuffled_people) {
        if (other_person.GetLocation() == person.GetLocation()) {
          contained_in_shuffled = true;
          break;
        }
      }
      REQUIRE(contained_in_shuffled);
    }
  }
}

TEST_CASE("Verify ApproachNewLocations() functionality") {
  SECTION("Method returns true immediately for 0-person arena") {
    epidemic_simulator::Simulator simulator(
        0, 100, 3, epidemic_simulator::Virus(1, 2, 2), 0, 0, 1, 1);
    simulator.ShufflePeople();
    REQUIRE(simulator.ApproachNewLocations());
  }
  SECTION("Method returns true for 1-person arena") {
    epidemic_simulator::Simulator simulator(
        1, 100, 3, epidemic_simulator::Virus(1, 2, 2), 0, 0, 1, 1);
    simulator.ShufflePeople();
    REQUIRE(simulator.ApproachNewLocations());
  }

  SECTION(
      "Method returns false until all people are at their new location for"
      "many-person arena") {
    epidemic_simulator::Simulator simulator(
        12, 100, 3, epidemic_simulator::Virus(1, 2, 2), 0, 0, 1, 1);
    simulator.ShufflePeople();
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
    epidemic_simulator::Simulator simulator(
        12, 100, 3, epidemic_simulator::Virus(1, 2, 2), 0, 0, 1, 1);
    simulator.ShufflePeople();
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

TEST_CASE("InfectNeighbors() works as intended") {
  SECTION(
      "Virus with 0% infectiousness does not infect anybody else for a "
      "12-person arena") {
    epidemic_simulator::Simulator simulator(
        12, 100, 1000, epidemic_simulator::Virus(0, 2, 2), 0, 0, 1, 1);
    for (size_t i = 0; i < 100; ++i) {
      const std::map<epidemic_simulator::Status, size_t>& frequencies =
          simulator.GetFrequencies();
      REQUIRE(frequencies.at(epidemic_simulator::Status::Infectious) +
                  frequencies.at(epidemic_simulator::Status::Incubating) +
                  frequencies.at(epidemic_simulator::Status::Immune) ==
              1);
      REQUIRE(frequencies.at(epidemic_simulator::Status::Vulnerable) == 11);
      simulator.ShufflePeople();
      simulator.InfectNeighbors();
    }
  }

  SECTION(
      "Virus with 0% infectiousness does not infect anybody else for a "
      "15-person arena") {
    epidemic_simulator::Simulator simulator(
        15, 100, 1000, epidemic_simulator::Virus(0, 2, 2), 0, 0, 1, 1);
    for (size_t i = 0; i < 100; ++i) {
      simulator.UpdateFrequencies();
      const std::map<epidemic_simulator::Status, size_t>& frequencies =
          simulator.GetFrequencies();
      REQUIRE(frequencies.at(epidemic_simulator::Status::Infectious) +
                  frequencies.at(epidemic_simulator::Status::Incubating) +
                  frequencies.at(epidemic_simulator::Status::Immune) ==
              1);
      REQUIRE(frequencies.at(epidemic_simulator::Status::Vulnerable) == 14);
      simulator.ShufflePeople();
      simulator.InfectNeighbors();
    }
  }

  SECTION(
      "Virus with 100% infectiousness infects each right neighbor of an "
      "infectious "
      "person") {
    epidemic_simulator::Simulator simulator(
        15, 100, 1000, epidemic_simulator::Virus(1, 2, 2), 0, 0, 1, 1);
    for (size_t i = 0; i < 100; ++i) {
      const std::vector<epidemic_simulator::Person>& initial_people =
          simulator.GetPeople();
      simulator.InfectNeighbors();
      const std::vector<epidemic_simulator::Person>& final_people =
          simulator.GetPeople();
      for (size_t j = 0; j < final_people.size(); ++j) {
        if (initial_people[j].GetStatus() ==
            epidemic_simulator::Status::Infectious) {
          REQUIRE(final_people[(j + 1) % final_people.size()].GetStatus() !=
                  epidemic_simulator::Status::Vulnerable);
        }
      }
      simulator.ShufflePeople();
    }
  }
  SECTION(
      "Virus with 100% infectiousness infects each left neighbor of an "
      "infectious person") {
    epidemic_simulator::Simulator simulator(
        15, 100, 1000, epidemic_simulator::Virus(1, 2, 2), 0, 0, 1, 1);
    for (size_t i = 0; i < 100; ++i) {
      const std::vector<epidemic_simulator::Person>& initial_people =
          simulator.GetPeople();
      simulator.InfectNeighbors();
      const std::vector<epidemic_simulator::Person>& final_people =
          simulator.GetPeople();
      for (size_t j = 0; j < final_people.size(); ++j) {
        if (initial_people[j].GetStatus() ==
            epidemic_simulator::Status::Infectious) {
          REQUIRE(
              final_people[(j - 1 + final_people.size()) % final_people.size()]
                  .GetStatus() != epidemic_simulator::Status::Vulnerable);
        }
      }
      simulator.ShufflePeople();
    }
  }
}

TEST_CASE("Frequencies are calculated correctly") {
  SECTION("Initial frequencies have 1 incubating and all other vulnerable") {
    epidemic_simulator::Simulator simulator(
        12, 100, 1000, epidemic_simulator::Virus(0, 2, 2), 0, 0, 1, 1);
    const std::map<epidemic_simulator::Status, size_t>& frequencies =
        simulator.GetFrequencies();
    REQUIRE(frequencies.at(epidemic_simulator::Status::Infectious) == 0);
    REQUIRE(frequencies.at(epidemic_simulator::Status::Incubating) == 1);
    REQUIRE(frequencies.at(epidemic_simulator::Status::Immune) == 0);
    REQUIRE(frequencies.at(epidemic_simulator::Status::Vulnerable) == 11);
  }

  SECTION("Virus with a 0% infectiousness updates frequencies correctly") {
    epidemic_simulator::Simulator simulator(
        15, 100, 1000, epidemic_simulator::Virus(0, 2, 2), 0, 0, 1, 1);
    for (size_t i = 0; i < 100; ++i) {
      size_t number_infectious = 0;
      size_t number_vulnerable = 0;
      size_t number_immune = 0;
      size_t number_incubating = 0;
      const std::vector<epidemic_simulator::Person>& people =
          simulator.GetPeople();
      for (const epidemic_simulator::Person& person : people) {
        switch (person.GetStatus()) {
          case epidemic_simulator::Status::Vulnerable:
            ++number_vulnerable;
            break;
          case epidemic_simulator::Status::Incubating:
            ++number_incubating;
            break;
          case epidemic_simulator::Status::Infectious:
            ++number_infectious;
            break;
          case epidemic_simulator::Status::Immune:
            ++number_immune;
            break;
        }
      }
      simulator.UpdateFrequencies();
      const std::map<epidemic_simulator::Status, size_t>& frequencies =
          simulator.GetFrequencies();
      REQUIRE(frequencies.at(epidemic_simulator::Status::Immune) ==
              number_immune);
      REQUIRE(frequencies.at(epidemic_simulator::Status::Vulnerable) ==
              number_vulnerable);
      REQUIRE(frequencies.at(epidemic_simulator::Status::Infectious) ==
              number_infectious);
      REQUIRE(frequencies.at(epidemic_simulator::Status::Incubating) ==
              number_incubating);
      simulator.ShufflePeople();
      simulator.InfectNeighbors();
    }
  }

  SECTION("Virus with a 50% infectiousness updates frequencies correctly") {
    epidemic_simulator::Simulator simulator(
        15, 100, 1000, epidemic_simulator::Virus(0.5, 2, 2), 0, 0, 1, 1);
    for (size_t i = 0; i < 100; ++i) {
      size_t number_infectious = 0;
      size_t number_vulnerable = 0;
      size_t number_immune = 0;
      size_t number_incubating = 0;
      const std::vector<epidemic_simulator::Person>& people =
          simulator.GetPeople();
      for (const epidemic_simulator::Person& person : people) {
        switch (person.GetStatus()) {
          case epidemic_simulator::Status::Vulnerable:
            ++number_vulnerable;
            break;
          case epidemic_simulator::Status::Incubating:
            ++number_incubating;
            break;
          case epidemic_simulator::Status::Infectious:
            ++number_infectious;
            break;
          case epidemic_simulator::Status::Immune:
            ++number_immune;
            break;
        }
      }
      simulator.UpdateFrequencies();

      const std::map<epidemic_simulator::Status, size_t>& frequencies =
          simulator.GetFrequencies();
      REQUIRE(frequencies.at(epidemic_simulator::Status::Immune) ==
              number_immune);
      REQUIRE(frequencies.at(epidemic_simulator::Status::Vulnerable) ==
              number_vulnerable);
      REQUIRE(frequencies.at(epidemic_simulator::Status::Infectious) ==
              number_infectious);
      REQUIRE(frequencies.at(epidemic_simulator::Status::Incubating) ==
              number_incubating);
      simulator.ShufflePeople();
      simulator.InfectNeighbors();
    }
  }

  SECTION("Virus with a 100% infectiousness updates frequencies correctly") {
    epidemic_simulator::Simulator simulator(
        15, 100, 1000, epidemic_simulator::Virus(1, 2, 2), 0, 0, 1, 1);
    for (size_t i = 0; i < 100; ++i) {
      size_t number_infectious = 0;
      size_t number_vulnerable = 0;
      size_t number_immune = 0;
      size_t number_incubating = 0;
      const std::vector<epidemic_simulator::Person>& people =
          simulator.GetPeople();
      for (const epidemic_simulator::Person& person : people) {
        switch (person.GetStatus()) {
          case epidemic_simulator::Status::Vulnerable:
            ++number_vulnerable;
            break;
          case epidemic_simulator::Status::Incubating:
            ++number_incubating;
            break;
          case epidemic_simulator::Status::Infectious:
            ++number_infectious;
            break;
          case epidemic_simulator::Status::Immune:
            ++number_immune;
            break;
        }
      }
      simulator.UpdateFrequencies();
      const std::map<epidemic_simulator::Status, size_t>& frequencies =
          simulator.GetFrequencies();
      REQUIRE(frequencies.at(epidemic_simulator::Status::Immune) ==
              number_immune);
      REQUIRE(frequencies.at(epidemic_simulator::Status::Vulnerable) ==
              number_vulnerable);
      REQUIRE(frequencies.at(epidemic_simulator::Status::Infectious) ==
              number_infectious);
      REQUIRE(frequencies.at(epidemic_simulator::Status::Incubating) ==
              number_incubating);
      simulator.ShufflePeople();
      simulator.InfectNeighbors();
    }
  }
}

TEST_CASE("Verify PerformNextFrame() functionality") {
  SECTION("People are shuffled when method is called for the first time") {
    epidemic_simulator::Simulator simulator(
        100, 100, 1, epidemic_simulator::Virus(0, 2, 2), 0, 0, 1, 1);
    const std::vector<epidemic_simulator::Person> initial_people =
        simulator.GetPeople();
    simulator.PerformNextFrame();
    const std::vector<epidemic_simulator::Person> final_people =
        simulator.GetPeople();
    bool is_shuffled = false;
    for (size_t i = 0; i < initial_people.size(); ++i) {
      if (initial_people[i].GetLocation() != final_people[i].GetLocation()) {
        is_shuffled = true;
        break;
      }
    }
    REQUIRE(is_shuffled);
  }

  SECTION("Neighbors are infected when method is called for the first time") {
    epidemic_simulator::Simulator simulator(
        15, 100, 1000, epidemic_simulator::Virus(1, 2, 2), 0, 0, 1, 1);
    for (size_t i = 0; i < 100; ++i) {
      const std::vector<epidemic_simulator::Person>& initial_people =
          simulator.GetPeople();
      simulator.InfectNeighbors();
      const std::vector<epidemic_simulator::Person>& final_people =
          simulator.GetPeople();
      for (size_t j = 0; j < final_people.size(); ++j) {
        if (initial_people[j].GetStatus() ==
            epidemic_simulator::Status::Infectious) {
          REQUIRE(final_people[(j + 1) % final_people.size()].GetStatus() !=
                  epidemic_simulator::Status::Vulnerable);
          REQUIRE(
              final_people[(j - 1 + final_people.size()) % final_people.size()]
                  .GetStatus() != epidemic_simulator::Status::Vulnerable);
        }
      }
    }
  }
  SECTION(
      "People approach their new locations when they are on their way to their "
      "new locations") {
    epidemic_simulator::Simulator simulator(
        100, 100, 1, epidemic_simulator::Virus(0, 2, 2), 0, 0, 1, 1);
    const std::vector<epidemic_simulator::Person> initial_people =
        simulator.GetPeople();
    simulator.PerformNextFrame();
    simulator.PerformNextFrame();
    const std::vector<epidemic_simulator::Person> final_people =
        simulator.GetPeople();
    for (size_t i = 0; i < initial_people.size(); ++i) {
      REQUIRE(initial_people[i].GetLocation() != final_people[i].GetLocation());
    }
  }

  SECTION("People are infected when they are at their new locations") {
    epidemic_simulator::Simulator simulator(
        15, 100, 1000, epidemic_simulator::Virus(1, 2, 2), 0, 0, 1, 1);
    simulator.PerformNextFrame();
    simulator.PerformNextFrame();
    simulator.PerformNextFrame();
    for (size_t i = 0; i < 100; ++i) {
      const std::vector<epidemic_simulator::Person>& initial_people =
          simulator.GetPeople();
      simulator.InfectNeighbors();
      const std::vector<epidemic_simulator::Person>& final_people =
          simulator.GetPeople();
      for (size_t j = 0; j < final_people.size(); ++j) {
        if (initial_people[j].GetStatus() ==
            epidemic_simulator::Status::Infectious) {
          REQUIRE(final_people[(j + 1) % final_people.size()].GetStatus() !=
                  epidemic_simulator::Status::Vulnerable);
          REQUIRE(
              final_people[(j - 1 + final_people.size()) % final_people.size()]
                  .GetStatus() != epidemic_simulator::Status::Vulnerable);
        }
      }
    }
  }

  SECTION("People are shuffled when they are at their new locations") {
    epidemic_simulator::Simulator simulator(
        100, 100, 1000, epidemic_simulator::Virus(0, 2, 2), 0, 0, 1, 1);
    simulator.PerformNextFrame();
    const std::vector<epidemic_simulator::Person> initial_people =
        simulator.GetPeople();
    simulator.PerformNextFrame();
    simulator.PerformNextFrame();

    const std::vector<epidemic_simulator::Person> final_people =
        simulator.GetPeople();
    bool is_shuffled = false;
    for (size_t i = 0; i < initial_people.size(); ++i) {
      if (initial_people[i].GetLocation() != final_people[i].GetLocation()) {
        is_shuffled = true;
        break;
      }
    }
    REQUIRE(is_shuffled);
  }
}

TEST_CASE("Verify Graph drawing functionality") {
  SECTION("Graph bars are initially generated correctly") {
    epidemic_simulator::Simulator simulator(
        1, 100, 1000, epidemic_simulator::Virus(0, 2, 2), 100, 100, 1, 1);
    const std::vector<ColumnStatus>& bars = simulator.GetBars();
    REQUIRE(bars.size() == 4);
    REQUIRE(bars[0].first == epidemic_simulator::Status::Vulnerable);
    REQUIRE(bars[1].first == epidemic_simulator::Status::Immune);
    REQUIRE(bars[2].first == epidemic_simulator::Status::Incubating);
    REQUIRE(bars[3].first == epidemic_simulator::Status::Infectious);
    REQUIRE(bars[0].second.getUpperLeft() == glm::vec2(0, 0));
    REQUIRE(bars[0].second.getLowerRight() == glm::vec2(100, 0));
    REQUIRE(bars[1].second.getUpperLeft() == glm::vec2(0, 0));
    REQUIRE(bars[1].second.getLowerRight() == glm::vec2(100, 0));
    REQUIRE(bars[2].second.getUpperLeft() == glm::vec2(0, 0));
    REQUIRE(bars[2].second.getLowerRight() == glm::vec2(100, 100));
    REQUIRE(bars[3].second.getUpperLeft() == glm::vec2(0, 100));
    REQUIRE(bars[3].second.getLowerRight() == glm::vec2(100, 100));
  }

  SECTION(
      "Graph bars are generated correctly after 2 days") {
    epidemic_simulator::Simulator simulator(
        1, 100, 1000, epidemic_simulator::Virus(0, 2, 2), 100, 100, 1, 1);
    simulator.PerformNextFrame();
    const std::vector<ColumnStatus>& bars = simulator.GetBars();
    REQUIRE(bars.size() == 8);
    REQUIRE(bars[0].first == epidemic_simulator::Status::Vulnerable);
    REQUIRE(bars[1].first == epidemic_simulator::Status::Immune);
    REQUIRE(bars[2].first == epidemic_simulator::Status::Incubating);
    REQUIRE(bars[3].first == epidemic_simulator::Status::Infectious);
    REQUIRE(bars[4].first == epidemic_simulator::Status::Vulnerable);
    REQUIRE(bars[5].first == epidemic_simulator::Status::Immune);
    REQUIRE(bars[6].first == epidemic_simulator::Status::Incubating);
    REQUIRE(bars[7].first == epidemic_simulator::Status::Infectious);
    REQUIRE(bars[0].second.getUpperLeft() == glm::vec2(0, 0));
    REQUIRE(bars[0].second.getLowerRight() == glm::vec2(50, 0));
    REQUIRE(bars[1].second.getUpperLeft() == glm::vec2(0, 0));
    REQUIRE(bars[1].second.getLowerRight() == glm::vec2(50, 0));
    REQUIRE(bars[2].second.getUpperLeft() == glm::vec2(0, 0));
    REQUIRE(bars[2].second.getLowerRight() == glm::vec2(50, 100));
    REQUIRE(bars[3].second.getUpperLeft() == glm::vec2(0, 100));
    REQUIRE(bars[3].second.getLowerRight() == glm::vec2(50, 100));
    REQUIRE(bars[4].second.getUpperLeft() == glm::vec2(50, 0));
    REQUIRE(bars[4].second.getLowerRight() == glm::vec2(100, 0));
    REQUIRE(bars[5].second.getUpperLeft() == glm::vec2(50, 0));
    REQUIRE(bars[5].second.getLowerRight() == glm::vec2(100, 0));
    REQUIRE(bars[6].second.getUpperLeft() == glm::vec2(50, 0));
    REQUIRE(bars[6].second.getLowerRight() == glm::vec2(100, 100));
    REQUIRE(bars[7].second.getUpperLeft() == glm::vec2(50, 100));
    REQUIRE(bars[7].second.getLowerRight() == glm::vec2(100, 100));
  }

  SECTION(
      "Graph bars are generated correctly after 4 days") {
    epidemic_simulator::Simulator simulator(
        1, 100, 1000, epidemic_simulator::Virus(0, 0, 0), 100, 100, 1, 1);
    simulator.PerformNextFrame();
    simulator.PerformNextFrame();
    simulator.PerformNextFrame();
    simulator.PerformNextFrame();
    simulator.PerformNextFrame();
    const std::vector<ColumnStatus>& bars = simulator.GetBars();
    REQUIRE(bars.size() == 16);
    REQUIRE(bars[0].first == epidemic_simulator::Status::Vulnerable);
    REQUIRE(bars[1].first == epidemic_simulator::Status::Immune);
    REQUIRE(bars[2].first == epidemic_simulator::Status::Incubating);
    REQUIRE(bars[3].first == epidemic_simulator::Status::Infectious);
    REQUIRE(bars[4].first == epidemic_simulator::Status::Vulnerable);
    REQUIRE(bars[5].first == epidemic_simulator::Status::Immune);
    REQUIRE(bars[6].first == epidemic_simulator::Status::Incubating);
    REQUIRE(bars[7].first == epidemic_simulator::Status::Infectious);
    REQUIRE(bars[8].first == epidemic_simulator::Status::Vulnerable);
    REQUIRE(bars[9].first == epidemic_simulator::Status::Immune);
    REQUIRE(bars[10].first == epidemic_simulator::Status::Incubating);
    REQUIRE(bars[11].first == epidemic_simulator::Status::Infectious);
    REQUIRE(bars[12].first == epidemic_simulator::Status::Vulnerable);
    REQUIRE(bars[13].first == epidemic_simulator::Status::Immune);
    REQUIRE(bars[14].first == epidemic_simulator::Status::Incubating);
    REQUIRE(bars[15].first == epidemic_simulator::Status::Infectious);
    REQUIRE(bars[0].second.getUpperLeft() == glm::vec2(0, 0));
    REQUIRE(bars[0].second.getLowerRight() == glm::vec2(25, 0));
    REQUIRE(bars[1].second.getUpperLeft() == glm::vec2(0, 0));
    REQUIRE(bars[1].second.getLowerRight() == glm::vec2(25, 0));
    REQUIRE(bars[2].second.getUpperLeft() == glm::vec2(0, 0));
    REQUIRE(bars[2].second.getLowerRight() == glm::vec2(25, 0));
    REQUIRE(bars[3].second.getUpperLeft() == glm::vec2(0, 0));
    REQUIRE(bars[3].second.getLowerRight() == glm::vec2(25, 100));
    REQUIRE(bars[4].second.getUpperLeft() == glm::vec2(25, 0));
    REQUIRE(bars[4].second.getLowerRight() == glm::vec2(50, 0));
    REQUIRE(bars[5].second.getUpperLeft() == glm::vec2(25, 0));
    REQUIRE(bars[5].second.getLowerRight() == glm::vec2(50, 100));
    REQUIRE(bars[6].second.getUpperLeft() == glm::vec2(25, 100));
    REQUIRE(bars[6].second.getLowerRight() == glm::vec2(50, 100));
    REQUIRE(bars[7].second.getUpperLeft() == glm::vec2(25, 100));
    REQUIRE(bars[7].second.getLowerRight() == glm::vec2(50, 100));
    REQUIRE(bars[8].second.getUpperLeft() == glm::vec2(50, 0));
    REQUIRE(bars[8].second.getLowerRight() == glm::vec2(75, 0));
    REQUIRE(bars[9].second.getUpperLeft() == glm::vec2(50, 0));
    REQUIRE(bars[9].second.getLowerRight() == glm::vec2(75, 100));
    REQUIRE(bars[10].second.getUpperLeft() == glm::vec2(50, 100));
    REQUIRE(bars[10].second.getLowerRight() == glm::vec2(75, 100));
    REQUIRE(bars[11].second.getUpperLeft() == glm::vec2(50, 100));
    REQUIRE(bars[11].second.getLowerRight() == glm::vec2(75, 100));
    REQUIRE(bars[12].second.getUpperLeft() == glm::vec2(75, 0));
    REQUIRE(bars[12].second.getLowerRight() == glm::vec2(100, 0));
    REQUIRE(bars[13].second.getUpperLeft() == glm::vec2(75, 0));
    REQUIRE(bars[13].second.getLowerRight() == glm::vec2(100, 100));
    REQUIRE(bars[14].second.getUpperLeft() == glm::vec2(75, 100));
    REQUIRE(bars[14].second.getLowerRight() == glm::vec2(100, 100));
    REQUIRE(bars[15].second.getUpperLeft() == glm::vec2(75, 100));
    REQUIRE(bars[15].second.getLowerRight() == glm::vec2(100, 100));
  }
}