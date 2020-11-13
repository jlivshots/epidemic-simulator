#ifndef FINAL_PROJECT_JLIVSHOTS_PERSON_H
#define FINAL_PROJECT_JLIVSHOTS_PERSON_H

#include "cinder/gl/gl.h"

namespace epidemic_simulator {
class Person {
 public:
  explicit Person(const glm::vec2& position);

  bool MoveTowardLocation(const glm::vec2& location, float speed);

  const glm::vec2& GetLocation() const;

 private:
  glm::vec2 position_;
};
}  // namespace epidemic_simulator

#endif  // FINAL_PROJECT_JLIVSHOTS_PERSON_H