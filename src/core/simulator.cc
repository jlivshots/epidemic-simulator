#include "core/simulator.h"

#include <random>

namespace epidemic_simulator {

Simulator::Simulator(size_t number_people, double arena_radius) {
  for (size_t i = 0; i < number_people; ++i) {
    double angle = 2 * i * M_PI / number_people;
    glm::vec2 position(arena_radius * cos(angle), arena_radius * sin(angle));
    slots_.push_back(position);
    people_.emplace_back(position);
  }
}

bool Simulator::ApproachNewLocations() {
  bool all_people_arrived = true;
  for (size_t i = 0; i< people_.size(); ++i) {
    if(!people_[i].MoveTowardLocation(slots_[i], 6.0f)) {
      all_people_arrived = false;
    }
    ++i;
  }
  return all_people_arrived;
}
const std::vector<Person>& Simulator::GetPeople() const {
  return people_;
}
const std::vector<glm::vec2>& Simulator::GetSlots() const {
  return slots_;
}

void Simulator::ShuffleSlots() {
  std::shuffle(slots_.begin(), slots_.end(),
               std::mt19937(std::random_device()()));
}
}  // namespace epidemic_simulator