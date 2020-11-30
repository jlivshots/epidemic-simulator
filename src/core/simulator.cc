#include "core/simulator.h"

#include <random>

namespace epidemic_simulator {

Simulator::Simulator(size_t number_people, double arena_radius, float speed,
                     const epidemic_simulator::Virus& virus, double graph_width,
                     double graph_height, size_t vertical_label_interval,
                     size_t horizontal_label_interval)
    : speed_(speed),
      virus_(virus),
      infectiousness_(virus.GetInfectiousness()),
      at_slots_(true),
      graph_(graph_width, graph_height, number_people, horizontal_label_interval) {
  for (size_t i = 0; i < number_people; ++i) {
    // Finds the radian angle of the current person's location relative to the
    // x-axis as 0 degrees.
    double angle = 2 * i * M_PI / number_people;
    glm::vec2 position(arena_radius * cos(angle), arena_radius * sin(angle));
    slots_.push_back(position);
    people_.emplace_back(position);
  }
  if (!people_.empty()) {
    people_[0].Infect(virus_);
  }
  UpdateFrequencies();
  graph_.GenerateVerticalLabels(vertical_label_interval);
}

bool Simulator::ApproachNewLocations() {
  bool all_people_arrived = true;
  for (size_t i = 0; i < people_.size(); ++i) {
    if (!people_[i].MoveTowardLocation(slots_[i], speed_)) {
      all_people_arrived = false;
    }
  }
  return all_people_arrived;
}

void Simulator::ShufflePeople() {
  std::shuffle(people_.begin(), people_.end(),
               std::mt19937(std::random_device()()));
}

void Simulator::InfectNeighbors() {
  for (Person& person : people_) {
    person.PassOneDay();
  }

  for (size_t i = 0; i < people_.size(); ++i) {
    if (people_[i].GetStatus() == Status::Infectious) {
      if ((double)rand() / RAND_MAX < infectiousness_) {
        size_t right_index = (i + 1) % people_.size();
        --frequencies_[people_[right_index].GetStatus()];
        people_[right_index].Infect(virus_);
        ++frequencies_[people_[right_index].GetStatus()];
      }
      if ((double)rand() / RAND_MAX < infectiousness_) {
        size_t left_index = (i - 1 + people_.size()) % people_.size();
        --frequencies_[people_[left_index].GetStatus()];
        people_[left_index].Infect(virus_);
        ++frequencies_[people_[left_index].GetStatus()];
      }
    }
  }
}

void Simulator::PerformNextFrame() {
  if (!at_slots_) {
    at_slots_ = ApproachNewLocations();
  } else {
    InfectNeighbors();
    ShufflePeople();
    UpdateFrequencies();
    at_slots_ = false;
  }
}

void Simulator::UpdateFrequencies() {
  frequencies_.clear();
  frequencies_.insert(std::make_pair(Status::Vulnerable, 0));
  frequencies_.insert(std::make_pair(Status::Infectious, 0));
  frequencies_.insert(std::make_pair(Status::Incubating, 0));
  frequencies_.insert(std::make_pair(Status::Immune, 0));
  for (const Person& person : people_) {
    ++frequencies_[person.GetStatus()];
  }
  graph_.AddDay(frequencies_);
  graph_.GenerateBars();
  graph_.GenerateHorizontalLabels();
}

const std::vector<ColumnStatus>& Simulator::GetBars() const {
  return graph_.GetBars();
}
const std::map<Status, size_t>& Simulator::GetFrequencies() const {
  return frequencies_;
}

const std::vector<Person>& Simulator::GetPeople() const {
  return people_;
}

const std::vector<glm::vec2>& Simulator::GetSlots() const {
  return slots_;
}

const std::vector<LocatedLabel>& Simulator::GetHorizontalLabels() const {
  return graph_.GetHorizontalLabels();
}

const std::vector<LocatedLabel>& Simulator::GetVerticalLabels() const {
  return graph_.GetVerticalLabels();
}
}  // namespace epidemic_simulator