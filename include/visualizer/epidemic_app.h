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
  void SetStatusFromColor(Status status);
  void DrawLegend();
  const size_t kNumberPeople = 5000;
  const float kPersonRadius = 4;
  const float kArenaRadius = 400;
  const glm::vec2 kArenaCenter = glm::vec2(400, 500);
  const glm::vec2 kGraphTopLeft = glm::vec2(850, 300);
  const double kGraphWidth = 500;
  const double kGraphHeight = 500;
  const float kSpeed = 1000;
  const Virus kVirus = Virus(0.1, 2, 8);

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
