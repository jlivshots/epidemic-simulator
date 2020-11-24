#include "core/graph.h"

#include "core/person.h"

epidemic_simulator::Graph::Graph(const glm::vec2& top_left_corner, size_t width,
                                 size_t height)
    : number_days_(0),
      top_wall_(top_left_corner.y),
      left_wall_(top_left_corner.x),
      height_(height),
      width_(width) {
}

const std::vector<ColumnStatus>& epidemic_simulator::Graph::GetBars() const {
  return bars_;
}

void epidemic_simulator::Graph::AddDay(
    const std::map<Status, size_t>& frequencies) {
}

void epidemic_simulator::Graph::GenerateBars() {
}
