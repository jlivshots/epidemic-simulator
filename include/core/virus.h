#ifndef EPIDEMIC_SIMULATOR_VIRUS_H
#define EPIDEMIC_SIMULATOR_VIRUS_H

namespace epidemic_simulator {
/**
 * Represents a virus and its infection characteristics.
 */
class Virus {
 public:
  /**
   * Instantiates a new Virus object.
   * @param infectiousness a double between 0-1 where 1 represents 100%
   * transmission and 0 represents 0% chance of infection.
   * @param incubation_period the number of days that someone is infectious
   * without being contagious.
   * @param infectious_period the number of days that someone is infectious.
   * @throw std::invalid_argument if infectiousness is not between 0-1.
   */
  Virus(double infectiousness, size_t incubation_period,
        size_t infectious_period);
  double GetInfectiousness() const;
  size_t GetIncubationPeriod() const;
  size_t GetInfectiousPeriod() const;

 private:
  double infectiousness_;
  size_t incubation_period_;
  size_t infectious_period_;
};
}  // namespace epidemic_simulator
#endif  // EPIDEMIC_SIMULATOR_VIRUS_H
