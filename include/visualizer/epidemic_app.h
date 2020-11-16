#ifndef FINAL_PROJECT_JLIVSHOTS_EPIDEMIC_APP_H
#define FINAL_PROJECT_JLIVSHOTS_EPIDEMIC_APP_H

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "core/person.h"
#include "core/simulator.h"
#include "core/virus.h"

/**
 * Simulates the spread of a virus over time.
 */
namespace epidemic_simulator {
namespace visualizer {
class EpidemicSimulatorApp : public ci::app::App {
 public:
  /** Creates a new simulator app instance. **/
  EpidemicSimulatorApp();

  /** Draws the next frame of the simulation. **/
  void draw() override;

 private:
  const size_t kNumberPeople = 100;
  const float kPersonSize = 6;
  const float kArenaRadius = 150;
  const glm::vec2 kArenaCenter = glm::vec2(400, 500);
  const float kSpeed = 5;
  const Virus kVirus = Virus(0.15, 2, 5);

  const double kWindowWidth = 1400;
  const double kWindowHeight = 1000;
  const ci::Color kVulnerableColor = ci::Color("blue");
  const ci::Color kIncubatingColor = ci::Color("orange");
  const ci::Color kInfectiousColor = ci::Color("red");
  const ci::Color kImmuneColor = ci::Color("green");

  epidemic_simulator::Simulator simulator_;
};
}  // namespace visualizer
}  // namespace epidemic_simulator

#endif  // FINAL_PROJECT_JLIVSHOTS_EPIDEMIC_APP_H
