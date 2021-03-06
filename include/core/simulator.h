#ifndef FINAL_PROJECT_JLIVSHOTS_SIMULATION_H
#define FINAL_PROJECT_JLIVSHOTS_SIMULATION_H
#include <vector>

#include "cinder/gl/gl.h"
#include "core/graph.h"
#include "core/person.h"
#include "core/virus.h"

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
   * @param graph_width the width of the stacked bar chart.
   * @param graph_height the height of the stacked bar chart.
   * @param vertical_label_interval the interval for the vertical axis labels.
   * @param initial_horizontal_label_interval the initial interval for the
   * horizontal axis labels.
   */
  Simulator(size_t number_people, double arena_radius, float speed,
            const Virus& virus, double graph_width, double graph_height,
            size_t vertical_label_interval,
            size_t initial_horizontal_label_interval);

  /**
   * Iterates through each Person in people_ and moves then 1 speed_ closer to
   * their corresponding location in slots_.
   * @return true if all people have reached their new slot, false otherwise.
   */
  bool ApproachNewLocations();

  /** Shuffles people_ to a random permutation. */
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

  /** Updates frequencies_ with the current frequencies of each Status. */
  void UpdateFrequencies();

  void SetSpeed(float speed);
  const std::vector<Person>& GetPeople() const;
  const std::vector<glm::vec2>& GetSlots() const;
  const std::vector<ColumnStatus>& GetBars() const;
  const std::map<Status, size_t>& GetFrequencies() const;
  const std::vector<LocatedLabel>& GetHorizontalLabels() const;
  const std::vector<LocatedLabel>& GetVerticalLabels() const;

 private:
  /** All vec2 positions on the circle, in order as traversed from 0-2PI. */
  std::vector<glm::vec2> slots_;

  /** The people within the simulation. */
  std::vector<Person> people_;

  /** The speed of travel around the arena. */
  float speed_;

  /** The infectiousness of the virus. */
  double infectiousness_;

  /** The virus to be modeled. */
  Virus virus_;

  /** True if all people are at their slot, false otherwise. */
  bool at_slots_;

  /** The frequency of each Status within the simulation. */
  std::map<Status, size_t> frequencies_;

  /** The graphical representation of the simulation. */
  Graph graph_;
};
}  // namespace epidemic_simulator

#endif  // FINAL_PROJECT_JLIVSHOTS_SIMULATION_H