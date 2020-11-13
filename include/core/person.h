#ifndef FINAL_PROJECT_JLIVSHOTS_PERSON_H
#define FINAL_PROJECT_JLIVSHOTS_PERSON_H

#include "cinder/gl/gl.h"

namespace epidemic_simulator {
class Person {
 public:
  Person(const glm::vec2& current_position, const glm::vec2& target_position);

  bool MoveTowardLocation(glm::vec2& location);

 private:
  glm::vec2 position_;
  glm::vec2 target_position_;
};
}  // namespace epidemic_simulator

#endif  // FINAL_PROJECT_JLIVSHOTS_PERSON_H