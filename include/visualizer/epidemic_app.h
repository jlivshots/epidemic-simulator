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
  std::string SetAndGetColorFromStatus(const Status& status) const;


  void DrawLegend();

  void DrawVerticalAxis();

  void DrawHorizontalAxis();


  const size_t kNumberPeople = 500;
  const float kSpeed = 30;
  const Virus kVirus = Virus(0.2, 2, 5);
  const float kPersonRadius = 2;
  const float kArenaRadius = 330;
  const glm::vec2 kArenaCenter = glm::vec2(400, 500);

  const glm::vec2 kGraphTopLeft = glm::vec2(880, 300);
  const double kGraphWidth = 500;
  const double kGraphHeight = 500;
  const size_t kVerticalLabelInterval = 100;
  const size_t kHorizontalLabelInterval = 10;
  constexpr static const float kAxisLabelSize = 20.0f;
  const glm::vec2 kVerticalAxisNameLocation = glm::vec2(800, 550);
  const glm::vec2 kHorizontalAxisNameLocation = glm::vec2(1130, 850);
  constexpr static const float kAxisNameSize = 35.0f;
  const double kDistanceGraphToHorizontalLabels = 20;

  const std::string kFont = "calibri";
  const ci::Color kTextColor = ci::Color("white");

  const glm::vec2 kLegendTopLeft = glm::vec2(850, 30);
  const glm::vec2 kLegendBottomRight = glm::vec2(1200, 200);
  const float kLegendIconSize = 15;

  constexpr static const float kLegendTextSize = 35.0f;
  const double kLegendMargin = 15;
  const glm::vec2 kFrequencyTopLeft = glm::vec2(1100, 30);

  const double kWindowWidth = 1400;
  const double kWindowHeight = 1000;
  const ci::Color kVulnerableColor = ci::Color("gray");
  const ci::Color kIncubatingColor = ci::Color("orange");
  const ci::Color kInfectiousColor = ci::Color("red");
  const ci::Color kImmuneColor = ci::Color("green");

  epidemic_simulator::Simulator simulator_;

  std::vector<LocatedLabel> vertical_labels_;
};
}  // namespace visualizer
}  // namespace epidemic_simulator

#endif  // FINAL_PROJECT_JLIVSHOTS_EPIDEMIC_APP_H
