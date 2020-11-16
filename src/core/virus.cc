#include "core/virus.h"

namespace epidemic_simulator {

Virus::Virus(double infectiousness, size_t incubation_period,
             size_t infectious_period)
    : infectiousness_(infectiousness),
      incubation_period_(incubation_period),
      infectious_period_(infectious_period) {
}
double Virus::GetInfectiousness() const {
  return infectiousness_;
}
size_t Virus::GetIncubationPeriod() const {
  return incubation_period_;
}
size_t Virus::GetInfectiousPeriod() const {
  return infectious_period_;
}
}  // namespace epidemic_simulator