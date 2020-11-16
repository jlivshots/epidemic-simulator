#include "core/person.h"

namespace epidemic_simulator {

Person::Person(const glm::vec2& current_position): position_(current_position), status_(Status::Vulnerable){
}

bool Person::MoveTowardLocation(const glm::vec2& target_location, float speed) {
  if(glm::distance(position_, target_location) <= speed) {
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
}  // namespace epidemic_simulator