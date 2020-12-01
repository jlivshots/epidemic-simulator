#include <core/graph.h>

#include <catch2/catch.hpp>

TEST_CASE("No people in simulation") {
  epidemic_simulator::Graph graph(100, 100, 0, 1);
  std::map<epidemic_simulator::Status, size_t> day;
  day.insert(std::make_pair(epidemic_simulator::Status::Vulnerable, 0));
  day.insert(std::make_pair(epidemic_simulator::Status::Infectious, 0));
  day.insert(std::make_pair(epidemic_simulator::Status::Incubating, 0));
  day.insert(std::make_pair(epidemic_simulator::Status::Immune, 0));
  SECTION("Graph Generates no bars") {
    graph.GenerateBars();
    REQUIRE(graph.GetBars().empty());
  }

  SECTION("Graph generates vertical label correctly") {
    graph.GenerateVerticalLabels(1);
    const std::vector<LocatedLabel>& labels = graph.GetVerticalLabels();
    REQUIRE(labels.empty());
  }

  SECTION("Horizontal labels are generated correctly for 0 days") {
    graph.GenerateHorizontalLabels();
    REQUIRE(graph.GetHorizontalLabels().empty());
  }

  SECTION("Horizontal labels are generated correctly for 1 day") {
    graph.AddDay(day);
    graph.GenerateHorizontalLabels();
    const std::vector<LocatedLabel>& labels = graph.GetHorizontalLabels();
    REQUIRE(labels.size() == 1);
  }

  SECTION("Horizontal labels are correctly rescaled on 10th day") {
    for (size_t i = 0; i < 9; ++i) {
      graph.AddDay(day);
    }
    graph.GenerateHorizontalLabels();
    const std::vector<LocatedLabel>& initial_labels =
        graph.GetHorizontalLabels();
    REQUIRE(initial_labels.size() == 9);
    graph.AddDay(day);
    graph.GenerateHorizontalLabels();
    const std::vector<LocatedLabel>& final_labels = graph.GetHorizontalLabels();
    REQUIRE(final_labels.size() == 5);
    for (size_t i = 0; i < final_labels.size(); ++i) {
      REQUIRE(final_labels[i].first == (i + 1) * 2);
      REQUIRE(final_labels[i].second.y == 0);
      REQUIRE(final_labels[i].second.x == 20 * (i + 1));
    }
  }
}