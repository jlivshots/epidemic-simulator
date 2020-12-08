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

  SECTION("Graph generates no vertical labels for 0 days") {
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

  SECTION("Horizontal labels are correctly rescaled and located on 10th day") {
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

TEST_CASE("1 person in simulation") {
  epidemic_simulator::Graph graph(100, 100, 1, 1);

  SECTION("Graph Generates no bars for 0 days") {
    graph.GenerateBars();
    REQUIRE(graph.GetBars().empty());
  }

  SECTION("Graph generates no vertical labels for 0 days") {
    graph.GenerateVerticalLabels(1);
    const std::vector<LocatedLabel>& labels = graph.GetVerticalLabels();
    REQUIRE(labels.empty());
  }

  SECTION("Graph generates correct vertical labels for 1 day") {
    std::map<epidemic_simulator::Status, size_t> first_day;
    first_day.insert(std::make_pair(epidemic_simulator::Status::Vulnerable, 1));
    first_day.insert(std::make_pair(epidemic_simulator::Status::Infectious, 0));
    first_day.insert(std::make_pair(epidemic_simulator::Status::Incubating, 0));
    first_day.insert(std::make_pair(epidemic_simulator::Status::Immune, 0));
    graph.AddDay(first_day);
    graph.GenerateVerticalLabels(1);
    const std::vector<LocatedLabel>& labels = graph.GetVerticalLabels();
    REQUIRE(labels.size() == 2);
    REQUIRE(labels[0].first == 0);
    REQUIRE(labels[0].second.x == 0);
    REQUIRE(labels[0].second.y == 100);
    REQUIRE(labels[1].first == 1);
    REQUIRE(labels[1].second.x == 0);
    REQUIRE(labels[1].second.y == 0);
  }

  SECTION("Horizontal labels are generated correctly for 0 days") {
    graph.GenerateHorizontalLabels();
    REQUIRE(graph.GetHorizontalLabels().empty());
  }

  SECTION("Horizontal labels are generated correctly for 1 day") {
    std::map<epidemic_simulator::Status, size_t> first_day;
    first_day.insert(std::make_pair(epidemic_simulator::Status::Vulnerable, 0));
    first_day.insert(std::make_pair(epidemic_simulator::Status::Infectious, 1));
    first_day.insert(std::make_pair(epidemic_simulator::Status::Incubating, 0));
    first_day.insert(std::make_pair(epidemic_simulator::Status::Immune, 0));
    graph.AddDay(first_day);
    graph.GenerateHorizontalLabels();
    const std::vector<LocatedLabel>& labels = graph.GetHorizontalLabels();
    REQUIRE(labels.size() == 1);
    REQUIRE(labels[0].first == 1);
    REQUIRE(labels[0].second == glm::vec2(100, 0));
  }

  SECTION("Horizontal labels are correctly rescaled and located on 10th day") {
    std::map<epidemic_simulator::Status, size_t> first_day;
    first_day.insert(std::make_pair(epidemic_simulator::Status::Vulnerable, 0));
    first_day.insert(std::make_pair(epidemic_simulator::Status::Infectious, 0));
    first_day.insert(std::make_pair(epidemic_simulator::Status::Incubating, 1));
    first_day.insert(std::make_pair(epidemic_simulator::Status::Immune, 0));
    for (size_t i = 0; i < 9; ++i) {
      graph.AddDay(first_day);
    }
    graph.GenerateHorizontalLabels();
    const std::vector<LocatedLabel>& initial_labels =
        graph.GetHorizontalLabels();
    REQUIRE(initial_labels.size() == 9);
    graph.AddDay(first_day);
    graph.GenerateHorizontalLabels();
    const std::vector<LocatedLabel>& final_labels = graph.GetHorizontalLabels();
    REQUIRE(final_labels.size() == 5);
    for (size_t i = 0; i < final_labels.size(); ++i) {
      REQUIRE(final_labels[i].first == (i + 1) * 2);
      REQUIRE(final_labels[i].second.y == 0);
      REQUIRE(final_labels[i].second.x == 20 * (i + 1));
    }
  }

  SECTION("Bars are generated correctly for 1 day") {
    std::map<epidemic_simulator::Status, size_t> first_day;
    first_day.insert(std::make_pair(epidemic_simulator::Status::Vulnerable, 1));
    first_day.insert(std::make_pair(epidemic_simulator::Status::Infectious, 0));
    first_day.insert(std::make_pair(epidemic_simulator::Status::Incubating, 0));
    first_day.insert(std::make_pair(epidemic_simulator::Status::Immune, 0));
    graph.AddDay(first_day);
    graph.GenerateBars();
    const std::vector<ColumnStatus> bars = graph.GetBars();
    REQUIRE(bars.size() == 4);
    REQUIRE(bars[0].first == epidemic_simulator::Status::Vulnerable);
    REQUIRE(bars[0].second.getUpperLeft() == glm::vec2(0, 0));
    REQUIRE(bars[0].second.getLowerRight() == glm::vec2(100, 100));
    REQUIRE(bars[1].first == epidemic_simulator::Status::Immune);
    REQUIRE(bars[2].first == epidemic_simulator::Status::Incubating);
    REQUIRE(bars[3].first == epidemic_simulator::Status::Infectious);
    for (size_t i = 1; i < 4; ++i) {
      REQUIRE(bars[i].second.getUpperLeft() == glm::vec2(0, 100));
      REQUIRE(bars[i].second.getLowerRight() == glm::vec2(100, 100));
    }
  }

  SECTION("Bars are generated correctly for 2 days") {
    std::map<epidemic_simulator::Status, size_t> first_day;
    first_day.insert(std::make_pair(epidemic_simulator::Status::Vulnerable, 0));
    first_day.insert(std::make_pair(epidemic_simulator::Status::Infectious, 1));
    first_day.insert(std::make_pair(epidemic_simulator::Status::Incubating, 0));
    first_day.insert(std::make_pair(epidemic_simulator::Status::Immune, 0));
    graph.AddDay(first_day);
    std::map<epidemic_simulator::Status, size_t> second_day;
    second_day.insert(
        std::make_pair(epidemic_simulator::Status::Vulnerable, 0));
    second_day.insert(
        std::make_pair(epidemic_simulator::Status::Infectious, 0));
    second_day.insert(
        std::make_pair(epidemic_simulator::Status::Incubating, 1));
    second_day.insert(std::make_pair(epidemic_simulator::Status::Immune, 0));
    graph.AddDay(second_day);
    graph.GenerateBars();
    const std::vector<ColumnStatus> bars = graph.GetBars();
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
    REQUIRE(bars[2].second.getLowerRight() == glm::vec2(50, 0));
    REQUIRE(bars[3].second.getUpperLeft() == glm::vec2(0, 0));
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
}

TEST_CASE("Multiple people in simulation") {
  epidemic_simulator::Graph first_graph(100, 100, 2, 1);
  epidemic_simulator::Graph second_graph(100, 100, 2, 2);

  SECTION("Graph Generates no bars") {
    first_graph.GenerateBars();
    REQUIRE(first_graph.GetBars().empty());
  }

  SECTION("Graph generates no vertical labels for 0 days") {
    first_graph.GenerateVerticalLabels(1);
    const std::vector<LocatedLabel>& labels = first_graph.GetVerticalLabels();
    REQUIRE(labels.empty());
  }

  SECTION("Graph generates correct vertical labels for 1 day with interval 2") {
    std::map<epidemic_simulator::Status, size_t> first_day;
    first_day.insert(std::make_pair(epidemic_simulator::Status::Vulnerable, 1));
    first_day.insert(std::make_pair(epidemic_simulator::Status::Infectious, 1));
    first_day.insert(std::make_pair(epidemic_simulator::Status::Incubating, 0));
    first_day.insert(std::make_pair(epidemic_simulator::Status::Immune, 0));
    first_graph.AddDay(first_day);
    first_graph.GenerateVerticalLabels(2);
    const std::vector<LocatedLabel>& labels = first_graph.GetVerticalLabels();
    REQUIRE(labels.size() == 2);
    REQUIRE(labels[0].first == 0);
    REQUIRE(labels[0].second.x == 0);
    REQUIRE(labels[0].second.y == 100);
    REQUIRE(labels[1].first == 2);
    REQUIRE(labels[1].second.x == 0);
    REQUIRE(labels[1].second.y == 0);
  }

  SECTION("Graph generates correct vertical labels for 1 day with interval 1") {
    std::map<epidemic_simulator::Status, size_t> first_day;
    first_day.insert(std::make_pair(epidemic_simulator::Status::Vulnerable, 1));
    first_day.insert(std::make_pair(epidemic_simulator::Status::Infectious, 1));
    first_day.insert(std::make_pair(epidemic_simulator::Status::Incubating, 0));
    first_day.insert(std::make_pair(epidemic_simulator::Status::Immune, 0));
    first_graph.AddDay(first_day);
    first_graph.GenerateVerticalLabels(1);
    const std::vector<LocatedLabel>& labels = first_graph.GetVerticalLabels();
    REQUIRE(labels.size() == 3);
    REQUIRE(labels[0].first == 0);
    REQUIRE(labels[0].second.x == 0);
    REQUIRE(labels[0].second.y == 100);
    REQUIRE(labels[1].first == 1);
    REQUIRE(labels[1].second.x == 0);
    REQUIRE(labels[1].second.y == 50);
    REQUIRE(labels[2].first == 2);
    REQUIRE(labels[2].second.x == 0);
    REQUIRE(labels[2].second.y == 0);
  }

  SECTION("Horizontal labels are generated correctly for 0 days") {
    first_graph.GenerateHorizontalLabels();
    REQUIRE(first_graph.GetHorizontalLabels().empty());
  }

  SECTION(
      "Horizontal labels are generated correctly for 1 day with initial "
      "interval 1") {
    std::map<epidemic_simulator::Status, size_t> first_day;
    first_day.insert(std::make_pair(epidemic_simulator::Status::Vulnerable, 0));
    first_day.insert(std::make_pair(epidemic_simulator::Status::Infectious, 1));
    first_day.insert(std::make_pair(epidemic_simulator::Status::Incubating, 0));
    first_day.insert(std::make_pair(epidemic_simulator::Status::Immune, 1));
    first_graph.AddDay(first_day);
    first_graph.GenerateHorizontalLabels();
    const std::vector<LocatedLabel>& labels = first_graph.GetHorizontalLabels();
    REQUIRE(labels.size() == 1);
  }

  SECTION(
      "Horizontal labels are correctly rescaled and located on 10th day with "
      "initial interval 1") {
    std::map<epidemic_simulator::Status, size_t> first_day;
    first_day.insert(std::make_pair(epidemic_simulator::Status::Vulnerable, 0));
    first_day.insert(std::make_pair(epidemic_simulator::Status::Infectious, 0));
    first_day.insert(std::make_pair(epidemic_simulator::Status::Incubating, 1));
    first_day.insert(std::make_pair(epidemic_simulator::Status::Immune, 1));
    for (size_t i = 0; i < 9; ++i) {
      first_graph.AddDay(first_day);
    }
    first_graph.GenerateHorizontalLabels();
    const std::vector<LocatedLabel>& initial_labels =
        first_graph.GetHorizontalLabels();
    REQUIRE(initial_labels.size() == 9);
    first_graph.AddDay(first_day);
    first_graph.GenerateHorizontalLabels();
    const std::vector<LocatedLabel>& final_labels =
        first_graph.GetHorizontalLabels();
    REQUIRE(final_labels.size() == 5);
    for (size_t i = 0; i < final_labels.size(); ++i) {
      REQUIRE(final_labels[i].first == (i + 1) * 2);
      REQUIRE(final_labels[i].second.y == 0);
      REQUIRE(final_labels[i].second.x == 20 * (i + 1));
    }
  }
  SECTION(
      "Horizontal labels are generated correctly for 1 day with initial "
      "interval 2") {
    std::map<epidemic_simulator::Status, size_t> first_day;
    first_day.insert(std::make_pair(epidemic_simulator::Status::Vulnerable, 0));
    first_day.insert(std::make_pair(epidemic_simulator::Status::Infectious, 1));
    first_day.insert(std::make_pair(epidemic_simulator::Status::Incubating, 0));
    first_day.insert(std::make_pair(epidemic_simulator::Status::Immune, 1));
    second_graph.AddDay(first_day);
    second_graph.GenerateHorizontalLabels();
    const std::vector<LocatedLabel>& labels =
        second_graph.GetHorizontalLabels();
    REQUIRE(labels.empty());
  }

  SECTION(
      "Horizontal labels are generated correctly for 2 days with initial "
      "interval 2") {
    std::map<epidemic_simulator::Status, size_t> first_day;
    first_day.insert(std::make_pair(epidemic_simulator::Status::Vulnerable, 0));
    first_day.insert(std::make_pair(epidemic_simulator::Status::Infectious, 1));
    first_day.insert(std::make_pair(epidemic_simulator::Status::Incubating, 0));
    first_day.insert(std::make_pair(epidemic_simulator::Status::Immune, 1));
    second_graph.AddDay(first_day);
    second_graph.AddDay(first_day);
    second_graph.GenerateHorizontalLabels();
    const std::vector<LocatedLabel>& labels =
        second_graph.GetHorizontalLabels();
    REQUIRE(labels.size() == 1);
    REQUIRE(labels[0].first == 2);
    REQUIRE(labels[0].second.x == 100);
    REQUIRE(labels[0].second.y == 0);
  }

  SECTION(
      "Horizontal labels are correctly rescaled and located on 20th day with "
      "initial interval 2") {
    std::map<epidemic_simulator::Status, size_t> first_day;
    first_day.insert(std::make_pair(epidemic_simulator::Status::Vulnerable, 0));
    first_day.insert(std::make_pair(epidemic_simulator::Status::Infectious, 0));
    first_day.insert(std::make_pair(epidemic_simulator::Status::Incubating, 1));
    first_day.insert(std::make_pair(epidemic_simulator::Status::Immune, 1));
    for (size_t i = 0; i < 19; ++i) {
      second_graph.AddDay(first_day);
    }
    second_graph.GenerateHorizontalLabels();
    const std::vector<LocatedLabel>& initial_labels =
        second_graph.GetHorizontalLabels();
    REQUIRE(initial_labels.size() == 9);
    second_graph.AddDay(first_day);
    second_graph.GenerateHorizontalLabels();
    const std::vector<LocatedLabel>& final_labels =
        second_graph.GetHorizontalLabels();
    REQUIRE(final_labels.size() == 5);
    for (size_t i = 0; i < final_labels.size(); ++i) {
      REQUIRE(final_labels[i].first == (i + 1) * 4);
      REQUIRE(final_labels[i].second.y == 0);
      REQUIRE(final_labels[i].second.x == 20 * (i + 1));
    }
  }

  SECTION("Bars are generated correctly for 1 day") {
    std::map<epidemic_simulator::Status, size_t> first_day;
    first_day.insert(std::make_pair(epidemic_simulator::Status::Vulnerable, 1));
    first_day.insert(std::make_pair(epidemic_simulator::Status::Infectious, 0));
    first_day.insert(std::make_pair(epidemic_simulator::Status::Incubating, 1));
    first_day.insert(std::make_pair(epidemic_simulator::Status::Immune, 0));
    first_graph.AddDay(first_day);
    first_graph.GenerateBars();
    const std::vector<ColumnStatus> bars = first_graph.GetBars();
    REQUIRE(bars.size() == 4);
    REQUIRE(bars[0].first == epidemic_simulator::Status::Vulnerable);
    REQUIRE(bars[1].first == epidemic_simulator::Status::Immune);
    REQUIRE(bars[2].first == epidemic_simulator::Status::Incubating);
    REQUIRE(bars[3].first == epidemic_simulator::Status::Infectious);
    REQUIRE(bars[0].second.getUpperLeft() == glm::vec2(0, 0));
    REQUIRE(bars[0].second.getLowerRight() == glm::vec2(100, 50));
    REQUIRE(bars[1].second.getUpperLeft() == glm::vec2(0, 50));
    REQUIRE(bars[1].second.getLowerRight() == glm::vec2(100, 50));
    REQUIRE(bars[2].second.getUpperLeft() == glm::vec2(0, 50));
    REQUIRE(bars[2].second.getLowerRight() == glm::vec2(100, 100));
    REQUIRE(bars[3].second.getUpperLeft() == glm::vec2(0, 100));
    REQUIRE(bars[3].second.getLowerRight() == glm::vec2(100, 100));
  }

  SECTION("Bars are generated correctly for 2 days") {
    std::map<epidemic_simulator::Status, size_t> first_day;
    first_day.insert(std::make_pair(epidemic_simulator::Status::Vulnerable, 1));
    first_day.insert(std::make_pair(epidemic_simulator::Status::Infectious, 0));
    first_day.insert(std::make_pair(epidemic_simulator::Status::Incubating, 1));
    first_day.insert(std::make_pair(epidemic_simulator::Status::Immune, 0));
    first_graph.AddDay(first_day);
    std::map<epidemic_simulator::Status, size_t> second_day;
    second_day.insert(
        std::make_pair(epidemic_simulator::Status::Vulnerable, 0));
    second_day.insert(
        std::make_pair(epidemic_simulator::Status::Infectious, 1));
    second_day.insert(
        std::make_pair(epidemic_simulator::Status::Incubating, 0));
    second_day.insert(std::make_pair(epidemic_simulator::Status::Immune, 1));
    first_graph.AddDay(second_day);
    first_graph.GenerateBars();
    const std::vector<ColumnStatus> bars = first_graph.GetBars();
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
    REQUIRE(bars[0].second.getLowerRight() == glm::vec2(50, 50));
    REQUIRE(bars[1].second.getUpperLeft() == glm::vec2(0, 50));
    REQUIRE(bars[1].second.getLowerRight() == glm::vec2(50, 50));
    REQUIRE(bars[2].second.getUpperLeft() == glm::vec2(0, 50));
    REQUIRE(bars[2].second.getLowerRight() == glm::vec2(50, 100));
    REQUIRE(bars[3].second.getUpperLeft() == glm::vec2(0, 100));
    REQUIRE(bars[3].second.getLowerRight() == glm::vec2(50, 100));
    REQUIRE(bars[4].second.getUpperLeft() == glm::vec2(50, 0));
    REQUIRE(bars[4].second.getLowerRight() == glm::vec2(100, 0));
    REQUIRE(bars[5].second.getUpperLeft() == glm::vec2(50, 0));
    REQUIRE(bars[5].second.getLowerRight() == glm::vec2(100, 50));
    REQUIRE(bars[6].second.getUpperLeft() == glm::vec2(50, 50));
    REQUIRE(bars[6].second.getLowerRight() == glm::vec2(100, 50));
    REQUIRE(bars[7].second.getUpperLeft() == glm::vec2(50, 50));
    REQUIRE(bars[7].second.getLowerRight() == glm::vec2(100, 100));
  }
}