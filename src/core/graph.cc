#include "core/graph.h"

namespace epidemic_simulator {
epidemic_simulator::Graph::Graph(double width, double height,
                                 size_t number_people,
                                 size_t initial_horizontal_label_interval)
    : number_days_(0),
      height_(height),
      width_(width),
      number_people_(number_people),
      horizontal_interval_(initial_horizontal_label_interval) {
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
  // The vertical order of the bars for each day. First Status will be at the
  // top, and the last status will be on the horizontal axis.
  static const std::vector<Status> kVerticalOrder = {
      Status::Vulnerable, Status::Immune, Status::Incubating,
      Status::Infectious};
  bars_.clear();
  if (number_people_ != 0) {
    double bar_width = width_ / number_days_;
    for (size_t day = 0; day < number_days_; ++day) {
      size_t lower_bound = 0;
      size_t upper_bound = 0;
      for (const Status& status : kVerticalOrder) {
        upper_bound += status_frequencies_[status][day];
        ci::Rectf boundary(
            glm::vec2(bar_width * day, lower_bound * height_ / number_people_),
            glm::vec2(bar_width * (day + 1),
                      upper_bound * height_ / number_people_));
        bars_.emplace_back(status, boundary);
        lower_bound = upper_bound;
      }
    }
  }
}

void epidemic_simulator::Graph::GenerateVerticalLabels(size_t interval) {
  vertical_labels_.clear();
  if (number_days_ != 0) {
    for (size_t i = 0; i <= number_people_; i += interval) {
      vertical_labels_.emplace_back(
          i, glm::vec2(0, height_ - height_ * i / number_people_));
    }
  }
}

const std::vector<LocatedLabel>& epidemic_simulator::Graph::GetVerticalLabels()
    const {
  return vertical_labels_;
}

void epidemic_simulator::Graph::GenerateHorizontalLabels() {
  horizontal_labels_.clear();
  if (number_days_ >= kMaxNumberLabels * horizontal_interval_) {
    horizontal_interval_ *= 2;
  }
  for (size_t i = horizontal_interval_; i <= number_days_;
       i += horizontal_interval_) {
    horizontal_labels_.emplace_back(i, glm::vec2(i * width_ / number_days_, 0));
  }
}

const std::vector<LocatedLabel>&
epidemic_simulator::Graph::GetHorizontalLabels() const {
  return horizontal_labels_;
}
}  // namespace epidemic_simulator