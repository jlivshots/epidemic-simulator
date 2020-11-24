#include "core/graph.h"

#include "core/person.h"

epidemic_simulator::Graph::Graph(double width, double height,
                                 size_t number_people)
    : number_days_(0),
      height_(height),
      width_(width),
      number_people_(number_people) {
  if (number_people == 0) {
    throw std::invalid_argument("Sorry, graph needs at least one person!");
  }
}

const std::vector<ColumnStatus>& epidemic_simulator::Graph::GetBars() const {
  return bars_;
}

void epidemic_simulator::Graph::AddDay(
    const std::map<Status, size_t>& frequencies) {
  ++number_days_;
  for (auto iterator : frequencies) {
    Status current_status = iterator.first;
    status_frequencies_[current_status].push_back(
        frequencies.at(current_status));
  }
}

void epidemic_simulator::Graph::GenerateBars() {
  double bar_width = width_ / number_days_;
  for (size_t day = 0; day < number_days_; ++day) {
    size_t lower_bound = 0;
    size_t upper_bound = 0;
    for (const Status& status : kVerticalOrder) {
      upper_bound += status_frequencies_[status][day];

      ci::Rectf boundary(glm::vec2(bar_width * day, lower_bound*height_/number_people_),
                         glm::vec2(bar_width * (day + 1), upper_bound*height_/number_people_));
      bars_.emplace_back(status, boundary);
      lower_bound = upper_bound;
    }
  }
}