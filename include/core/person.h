#ifndef FINAL_PROJECT_JLIVSHOTS_PERSON_H
#define FINAL_PROJECT_JLIVSHOTS_PERSON_H

#include "cinder/gl/gl.h"
#include "core/virus.h"

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

  void Infect(Virus virus);

  void PassOneDay();

  const glm::vec2& GetLocation() const;

  Status GetStatus() const;


 private:
  glm::vec2 position_;
  size_t days_incubating_remaining_;
  size_t days_infectious_remaining_;
  Status status_;
};
}  // namespace epidemic_simulator

#endif  // FINAL_PROJECT_JLIVSHOTS_PERSON_H