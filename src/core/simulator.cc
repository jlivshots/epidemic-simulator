#include "core/simulator.h"

#include <random>

namespace epidemic_simulator {

Simulator::Simulator(size_t number_people, double arena_radius, float speed,
                     const epidemic_simulator::Virus& virus)
    : speed_(speed), virus_(virus),
      infectiousness_(virus.GetInfectiousness()),
      incubation_period_(virus.GetIncubationPeriod()),
      infectious_period_(virus.GetInfectiousPeriod()) {
  for (size_t i = 0; i < number_people; ++i) {
    // Finds the radian angle of the current person's location relative to the
    // x-axis as 0 degrees.
    double angle = 2 * i * M_PI / number_people;
    glm::vec2 position(arena_radius * cos(angle), arena_radius * sin(angle));
    slots_.push_back(position);
    people_.emplace_back(position);
    current_person_index_ = 0;
  }
  if(!people_.empty()) {
    people_[0].Infect(virus_);
  }
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

const std::vector<Person>& Simulator::GetPeople() const {
  return people_;
}

const std::vector<glm::vec2>& Simulator::GetSlots() const {
  return slots_;
}

void Simulator::ShufflePeople() {
  std::shuffle(people_.begin(), people_.end(),
               std::mt19937(std::random_device()()));
}

void Simulator::InfectNeighbors() {
  for(Person& person: people_) {
    person.PassOneDay();
  }
    for(size_t i = 0; i<people_.size(); ++i) {
      if(people_[i].GetStatus()==Status::Infectious) {
        people_[(i+1)%people_.size()].Infect(virus_);
        people_[(i-1+people_.size())%people_.size()].Infect(virus_);
      }
    }
  }

}  // namespace epidemic_simulator