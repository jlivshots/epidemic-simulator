#include "core/person.h"

namespace epidemic_simulator {

Person::Person(const glm::vec2& current_position)
    : position_(current_position), status_(Status::Vulnerable) {
}

bool Person::MoveTowardLocation(const glm::vec2& target_location, float speed) {
  if (glm::distance(position_, target_location) <= speed) {
    position_ = target_location;
    return true;
  } else {
    position_ += glm::normalize(target_location - position_) * speed;
    return false;
  }
}

void Person::Infect(Virus virus) {
  if (status_ == Status::Vulnerable) {
    days_infectious_remaining_ = virus.GetInfectiousPeriod();
    days_incubating_remaining_ = virus.GetIncubationPeriod();
    if (days_incubating_remaining_ > 0) {
      status_ = Status::Incubating;
    } else {
      status_ = Status::Infectious;
    }
  }
}

void Person::SimulateOneDayPass() {
  if (status_ == Status::Incubating) {
    if (days_incubating_remaining_ == 0) {
      status_ = Status::Infectious;
    } else {
      --days_incubating_remaining_;
    }
  } else if (status_ == Status::Infectious) {
    if (days_infectious_remaining_ == 0) {
      status_ = Status::Immune;
    } else {
      --days_infectious_remaining_;
    }
  }
}

const glm::vec2& Person::GetLocation() const {
  return position_;
}

Status Person::GetStatus() const {
  return status_;
}
}  // namespace epidemic_simulator