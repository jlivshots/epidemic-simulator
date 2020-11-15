#ifndef FINAL_PROJECT_JLIVSHOTS_SIMULATION_H
#define FINAL_PROJECT_JLIVSHOTS_SIMULATION_H
#include <vector>

#include "cinder/gl/gl.h"
#include "core/person.h"
namespace epidemic_simulator {
class Simulator {
 public:
  Simulator(size_t number_people, double arena_radius, float speed);

  bool ApproachNewLocations();
  void ShuffleSlots();
  const std::vector<Person>& GetPeople() const;
  const std::vector<glm::vec2>& GetSlots() const;


 private:
  std::vector<glm::vec2> slots_;
  std::vector<Person> people_;
  float speed_;
  size_t current_person_index_;

};
}

#endif //FINAL_PROJECT_JLIVSHOTS_SIMULATION_H