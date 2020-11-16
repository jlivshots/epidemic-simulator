#ifndef EPIDEMIC_SIMULATOR_VIRUS_H
#define EPIDEMIC_SIMULATOR_VIRUS_H

namespace epidemic_simulator {
class Virus {
 public:
  Virus(double infectiousness, size_t incubation_period, size_t infectious_period);
  double GetInfectiousness() const;
  size_t GetIncubationPeriod() const;
  size_t GetInfectiousPeriod() const;
 private:
  double infectiousness_;
  size_t incubation_period_;
  size_t infectious_period_;
};
}
#endif  // EPIDEMIC_SIMULATOR_VIRUS_H
