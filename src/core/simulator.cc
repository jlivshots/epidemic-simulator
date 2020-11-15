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
  size_t i = 0;
  for (Person& person : people_) {
//        double new_index = ((people_.size()-1)/2 + i)% (people_.size()-1);
//        glm::vec2 target = slots_[(size_t )new_index];
//        person.MoveTowardLocation(slots_[((people_.size())/3 + i)%
//        (people_.size())], 9.0f);
//        ++i;
    person.MoveTowardLocation(slots_[i], 6.0f);
    ++i;
  }
  return false;
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