#include "core/virus.h"

#include <stdexcept>

namespace epidemic_simulator {

Virus::Virus(double infectiousness, size_t incubation_period,
             size_t infectious_period)
    : infectiousness_(infectiousness),
      incubation_period_(incubation_period),
      infectious_period_(infectious_period) {
  if(infectious_period==0) {
    throw std::invalid_argument("Virus must have a positive infectious period!");
  }
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