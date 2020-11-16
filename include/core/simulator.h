#ifndef FINAL_PROJECT_JLIVSHOTS_SIMULATION_H
#define FINAL_PROJECT_JLIVSHOTS_SIMULATION_H
#include <vector>

#include "cinder/gl/gl.h"
#include "core/person.h"
#include "core/virus.h"
namespace epidemic_simulator {
class Simulator {
 public:
  Simulator(size_t number_people, double arena_radius, float speed, const epidemic_simulator::Virus& virus);

  bool ApproachNewLocations();
  void ShuffleSlots();
  const std::vector<Person>& GetPeople() const;
  const std::vector<glm::vec2>& GetSlots() const;


 private:
  std::vector<glm::vec2> slots_;
  std::vector<Person> people_;
  float speed_;
  size_t current_person_index_;
  double infectiousness_;
  size_t incubation_period_;
  size_t infectious_period_;
  Virus virus_;
};
}

#endif //FINAL_PROJECT_JLIVSHOTS_SIMULATION_H