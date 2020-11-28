#ifndef FINAL_PROJECT_JLIVSHOTS_SIMULATION_H
#define FINAL_PROJECT_JLIVSHOTS_SIMULATION_H
#include <vector>

#include "cinder/gl/gl.h"
#include "core/person.h"
#include "core/virus.h"
#include "core/graph.h"

/**
 * Visually simulates the spread of a virus on a circular arena.
 */
namespace epidemic_simulator {
class Simulator {
 public:
  /**
   * Creates a new Simulator instance. Spaces people evenly around the arena.
   * Infects the person located at 0 radians relative to the x-axis. All
   * positions are relative to (0,0).
   * @param number_people the number of people in the arena.
   * @param arena_radius the radius of the arena.
   * @param speed the speed of people when moving to a new slot.
   * @param virus the Virus to be modelled in the simulation.
   */
  Simulator(size_t number_people, double arena_radius, float speed,
            const epidemic_simulator::Virus& virus, double graph_width, double graph_height, bool show_graph);

  /**
   * Iterates through each Person in people_ and moves then 1 speed_ closer to
   * their corresponding location in slots_.
   * @return true if all people have reached their new slot, false otherwise.
   */
  bool ApproachNewLocations();

  /**
   * Shuffles people_ to a random permutation.
   */
  void ShufflePeople();

  /**
   * Each contagious person will infect their right and left neighbors with the
   * probability of infectiousness_.
   */
  void InfectNeighbors();

  /**
   * Shuffles people_ if all people are at their target location, otherwise
   * moves each person by 1 frame closer to their target slot.
   */
  void PerformNextFrame();

  void UpdateFrequencies();

  const std::vector<Person>& GetPeople() const;
  const std::vector<glm::vec2>& GetSlots() const;
  const std::vector<ColumnStatus>& GetBars() const;
  const std::map<Status, size_t>& GetFrequencies() const;
 private:
  /** All vec2 positions on the circle, in order as traversed from 0-2PI. **/
  std::vector<glm::vec2> slots_;
  std::vector<Person> people_;
  float speed_;
  double infectiousness_;
  Virus virus_;
  bool at_slots_;
  std::map<Status, size_t> frequencies_;
  Graph graph_;
  bool show_graph_;
};
}  // namespace epidemic_simulator

#endif  // FINAL_PROJECT_JLIVSHOTS_SIMULATION_H