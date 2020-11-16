#ifndef FINAL_PROJECT_JLIVSHOTS_PERSON_H
#define FINAL_PROJECT_JLIVSHOTS_PERSON_H

#include "cinder/gl/gl.h"

namespace epidemic_simulator {

enum class Status {
  Vulnerable,
  Incubating,
  Infectious,
  Immune,
};

class Person {
 public:
  explicit Person(const glm::vec2& position);

  bool MoveTowardLocation(const glm::vec2& location, float speed);



  const glm::vec2& GetLocation() const;

 private:
  glm::vec2 position_;
  size_t days_incubating_;
  size_t days_contagious_;
  Status status_;
};
}  // namespace epidemic_simulator

#endif  // FINAL_PROJECT_JLIVSHOTS_PERSON_H