#include "core/simulator.h"

namespace epidemic_simulator {

Simulator::Simulator(size_t number_people, double arena_radius) {
  for(size_t i =0; i<number_people; ++i) {
    double angle = 2 * i * M_PI / number_people;
    glm::vec2 position(arena_radius * cos(angle), arena_radius * sin(angle));
    slots_.push_back(position);
    people_.emplace_back(position);
  }
}

bool Simulator::ApproachNewLocations() {
  return false;
}
const std::vector<Person>& Simulator::GetPeople() const {
  return people_;
}
}  // namespace epidemic_simulator