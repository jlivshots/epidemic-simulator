#include "core/person.h"

namespace epidemic_simulator {

Person::Person(const glm::vec2& current_position)
    : position_(current_position), status_(Status::Vulnerable) {
}

bool Person::MoveTowardLocation(const glm::vec2& target_location, float speed) {
  if (glm::distance(position_, target_location) <= speed) {
    position_ = target_location;
    return true;
  }

  else {
    position_ += glm::normalize(target_location - position_) * speed;
    return false;
  }
}

const glm::vec2& Person::GetLocation() const {
  return position_;
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

void Person::PassOneDay() {
  if (status_ == Status::Incubating) {
    --days_incubating_remaining_;
    if (days_incubating_remaining_ == 0) {
      status_ = Status::Infectious;
    }
  } else if (status_ == Status::Infectious) {
    --days_infectious_remaining_;
    if (days_infectious_remaining_ == 0) {
      status_ = Status::Immune;
    }
  }

}


Status Person::GetStatus() const {
  return status_;
}
}  // namespace epidemic_simulator