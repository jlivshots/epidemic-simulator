#ifndef FINAL_PROJECT_JLIVSHOTS_PERSON_H
#define FINAL_PROJECT_JLIVSHOTS_PERSON_H

#include "cinder/gl/gl.h"
#include "core/virus.h"

namespace epidemic_simulator {

/**
 * Represents a person's viral status.
 * Vulnerable: they can be infected.
 * Incubating: infected but not yet contagious.
 * Infectious: infected and infectious.
 * Immune: recovered from virus, cannot contract it again.
 */
enum class Status {
  Vulnerable,
  Incubating,
  Infectious,
  Immune,
};

/**
 * Represents a person who can carry a virus. A Person has a location and a
 * viral Status.
 */
class Person {
 public:
  /**
   * Instantiates a new Person Object.
   * @param position the vec2 detailing the person's location relative to the
   * center of the arena.
   */
  explicit Person(const glm::vec2& position);

  /**
   * Moves the location of a person by the length of speed in the direction of
   * location. Returns true if person has arrived at the location.
   * @param location the target location to go towards.
   * @param speed the speed of one frame.
   * @return a bool representing if the person has arrived at the target
   * location.
   */
  bool MoveTowardLocation(const glm::vec2& location, float speed);

  /**
   * Infects the person if they weren't already infected. Sets
   * days_incubating_remaining and days_infectious_remaining to be the
   * corresponding instance variables of the virus parameter. If
   * days_incubating_remaining is zero, sets status_ to be infectious, otherwise
   * sets status_ to be incubating.
   * @param virus the Virus with which the person is infected.
   */
  void Infect(const Virus& virus);

  /**
   * If person is not infected, person remains unaltered. If status is
   * incubating and days_incubating_remaining is 0, status is updated to
   * infectious, otherwise days_incubating_remaining is decremented. If status
   * is infectious and days_infectious_remaining is 0, status is updated to
   * immune, otherwise days_infectious_remaining is decremented.
   */
  void SimulateOneDayPass();

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