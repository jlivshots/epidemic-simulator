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
  void SetStatusFromColor(const Status& status) const;
  void DrawLegend();
  const size_t kNumberPeople = 300;
  const float kPersonRadius = 4;
  const float kArenaRadius = 400;
  const glm::vec2 kArenaCenter = glm::vec2(400, 500);

  const glm::vec2 kGraphTopLeft = glm::vec2(850, 300);
  const double kGraphWidth = 500;
  const double kGraphHeight = 500;

  const glm::vec2 kLegendTopLeft = glm::vec2(850, 30);
  const glm::vec2 kLegendBottomRight = glm::vec2(1200, 200);
  const float kLegendIconSize = 15;
  const std::string kLegendFont = "calibri";
  const ci::Color kLegendColor = ci::Color("white");
  constexpr static const float kLegendFontSize = 18.0f;
  const double kLegendMargin = 15;

  const float kSpeed = 20;
  const Virus kVirus = Virus(0.2, 2, 4);

  const double kWindowWidth = 1400;
  const double kWindowHeight = 1000;
  const ci::Color kVulnerableColor = ci::Color("gray");
  const ci::Color kIncubatingColor = ci::Color("orange");
  const ci::Color kInfectiousColor = ci::Color("red");
  const ci::Color kImmuneColor = ci::Color("green");

  epidemic_simulator::Simulator simulator_;
};
}  // namespace visualizer
}  // namespace epidemic_simulator

#endif  // FINAL_PROJECT_JLIVSHOTS_EPIDEMIC_APP_H
