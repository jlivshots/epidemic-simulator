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
  /**
   * Sets the current Color to the one associated with status, and returns the
   * string name of the status.
   * @param status a Status enum.
   * @return an std::string corresponding to the name of the status.
   */
  std::string SetColorAndGetName(const Status& status) const;

  /**
   * Draws the legend box and frequency counts.
   */
  void DrawLegend();

  /**
   * Draws the vertical axis labels and title.
   */
  void DrawVerticalAxis();

  /**
   * Draws the horizontal axis labels and title.
   */
  void DrawHorizontalAxis();

  /** Virus and people **/
  static const size_t kNumberPeople = 250;
  const Virus kVirus = Virus(0.15, 1, 8);

  /** Window and speed**/
  constexpr static float kSpeed = 25;
  constexpr static double kWindowWidth = 1400;
  constexpr static double kWindowHeight = 1000;

  /** Arena **/
  constexpr static float kPersonRadius = 4;
  constexpr static float kArenaRadius = 330;
  const glm::vec2 kArenaCenter = glm::vec2(400, 500);

  /** Graph **/
  const glm::vec2 kGraphTopLeft = glm::vec2(880, 300);
  constexpr static double kGraphWidth = 500;
  constexpr static double kGraphHeight = 500;
  static const size_t kVerticalLabelInterval = 50;
  static const size_t kInitialHorizontalLabelInterval = 1;
  constexpr static float kAxisLabelSize = 20.0f;
  const glm::vec2 kVerticalAxisNameLocation = glm::vec2(800, 550);
  const glm::vec2 kHorizontalAxisNameLocation = glm::vec2(1130, 825);
  constexpr static float kAxisNameSize = 35.0f;

  /** Text **/
  const std::string kFont = "helvetica";
  const ci::Color kTextColor = ci::Color("white");

  /** Legend **/
  const glm::vec2 kLegendTopLeft = glm::vec2(850, 30);
  const glm::vec2 kLegendBottomRight = glm::vec2(1115, 200);
  constexpr static float kLegendIconSize = 15;
  constexpr static float kLegendTextSize = 35.0f;
  constexpr static double kLegendMargin = 15;
  const glm::vec2 kFrequencyTopLeft = glm::vec2(1100, 30);

  /** Status colors **/
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
