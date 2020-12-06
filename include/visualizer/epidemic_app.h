#ifndef FINAL_PROJECT_JLIVSHOTS_EPIDEMIC_APP_H
#define FINAL_PROJECT_JLIVSHOTS_EPIDEMIC_APP_H

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "core/button.h"
#include "core/person.h"
#include "core/simulator.h"
#include "core/slider.h"
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

  void mouseDown(ci::app::MouseEvent event) override;

  void mouseUp(ci::app::MouseEvent event) override;

  void mouseDrag(ci::app::MouseEvent event) override;

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

  void DrawSliders();

  void DrawPeopleSlider();

  void DrawIncubationSlider();

  void DrawInfectionSlider();

  void DrawContagiousnessSlider();

  void DrawButtons();


  /** Window and speed**/
  constexpr static float kSpeed = 33;
  constexpr static double kWindowWidth = 1400;
  constexpr static double kWindowHeight = 1000;

  /** Arena **/
  constexpr static float kPersonRadius = 4;
  constexpr static float kArenaRadius = 330;
  const glm::vec2 kArenaCenter = glm::vec2(375, 650);

  /** Graph **/
  const glm::vec2 kGraphTopLeft = glm::vec2(880, 360);
  constexpr static double kGraphWidth = 500;
  constexpr static double kGraphHeight = 500;
  constexpr static double kVerticalLabelIntervalFactor = 5.0;
  static const size_t kInitialHorizontalLabelInterval = 1;
  constexpr static float kAxisLabelSize = 20.0f;
  const glm::vec2 kVerticalAxisNameLocation = glm::vec2(800, 600);
  const glm::vec2 kHorizontalAxisNameLocation = glm::vec2(1130, 875);
  constexpr static float kAxisNameSize = 35.0f;

  /** Text **/
  const std::string kFont = "helvetica";
  const ci::Color kTextColor = ci::Color("white");

  /** Legend **/
  const glm::vec2 kLegendTopLeft = glm::vec2(975, 100);
  const glm::vec2 kLegendBottomRight = glm::vec2(1240, 300);
  constexpr static float kLegendIconSize = 15;
  constexpr static float kLegendTextSize = 35.0f;
  constexpr static double kLegendMargin = 15;
  const glm::vec2 kFrequencyTopLeft = glm::vec2(1225, 100);

  /** Status colors **/
  const ci::Color kVulnerableColor = ci::Color("gray");
  const ci::Color kIncubatingColor = ci::Color("orange");
  const ci::Color kInfectiousColor = ci::Color("red");
  const ci::Color kImmuneColor = ci::Color("green");

  /** Sliders **/
  const ci::Color kSliderColor = ci::Color("gray");
  constexpr static double kSliderWidth = 150;
  constexpr static float kSliderTextSize = 30;
  constexpr static double kSliderHeight = 35;
  constexpr static double kDragBoxWidth = 25;

  /** People slider **/
  const glm::vec2 kPeopleSliderTopLeft = glm::vec2(275, 85);
  static const size_t kMinNumberPeople = 1;
  static const size_t kMaxNumberPeople = 1000;

  /** Incubation slider **/
  const glm::vec2 kIncubationSliderTopLeft = glm::vec2(575, 85);
  static const size_t kMinIncubation = 0;
  static const size_t kMaxIncubation = 10;

  /** Infection slider **/
  const glm::vec2 kInfectionSliderTopLeft = glm::vec2(575, 200);
  static const size_t kMinInfection = 1;
  static const size_t kMaxInfection = 10;

  /** Contagiousness slider **/
  const glm::vec2 kContagiousnessSliderTopLeft = glm::vec2(275, 200);
  static const size_t kMinContagiousness = 0;
  static const size_t kMaxContagiousness = 100;

  /** Buttons **/
  constexpr static float kButtonTextSize = 50;
  const glm::vec2 kPlayButtonTopLeft = glm::vec2(30, 30);
  const glm::vec2 kPlayButtonBottomRight = glm::vec2(200, 200);
  const ci::Color kPlayButtonColor = ci::Color("Green");
  const glm::vec2 kPlayButtonTextLocation =
      (kPlayButtonTopLeft + kPlayButtonBottomRight) * 0.5f -
      glm::vec2(0, kButtonTextSize / 3);
  const glm::vec2 kResetButtonTopLeft = glm::vec2(30, 210);
  const glm::vec2 kResetButtonBottomRight = glm::vec2(200, 320);
  const ci::Color kResetButtonColor = ci::Color("Red");
  const glm::vec2 kResetButtonTextLocation =
      (kResetButtonTopLeft + kResetButtonBottomRight) * 0.5f -
      glm::vec2(0, kButtonTextSize / 3);

  epidemic_simulator::Simulator simulator_;
  Slider people_slider_;
  Slider incubation_slider_;
  Slider infection_slider_;
  Slider contagiousness_slider_;

  Button play_button_;
  Button reset_button_;
  std::vector<LocatedLabel> vertical_labels_;
};
}  // namespace visualizer
}  // namespace epidemic_simulator

#endif  // FINAL_PROJECT_JLIVSHOTS_EPIDEMIC_APP_H
