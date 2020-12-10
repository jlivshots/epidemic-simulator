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
 * Simulates the spread of a virus over time, and provides sliders and buttons
 * to set simulation speed and virus parameters.
 *
 * Note: slider/button logic and instance variables are maintained in this app
 * class because resetting the simulation when the reset button is pressed
 * requires creating a new simulator_ instance, which cannot be done from within
 * the Simulator class. Also, maintaining sliders and buttons within a simulator
 * would require an unnecessarily large number of parameters in the Simulator
 * Constructor.
 */
namespace epidemic_simulator {
namespace visualizer {
class EpidemicSimulatorApp : public ci::app::App {
 public:
  /** Creates a new simulator app instance. */
  EpidemicSimulatorApp();

  /**
   * Draws the next frame of the simulation. Calls the next frame of the
   * simulator if the play button is pressed.
   */
  void draw() override;

  /**
   * Begins dragging each slider and Clicking each button that the mouse is
   * hovering over.
   */
  void mouseDown(ci::app::MouseEvent event) override;

  /** Stops dragging each slider. */
  void mouseUp(ci::app::MouseEvent event) override;

  /** Updates each slider that the mouse might be dragging. */
  void mouseDrag(ci::app::MouseEvent event) override;

 private:
  /**
   * Sets the current Color to the one associated with status, and returns the
   * string name of the status.
   * @param status a Status enum.
   * @return the name of the status.
   */
  std::string SetColorAndGetName(const Status& status) const;

  /** Draws the legend box and frequency counts. */
  void DrawLegend();

  /** Draws the vertical axis labels and title. */
  void DrawVerticalAxis();

  /** Draws the horizontal axis labels and title. */
  void DrawHorizontalAxis();

  /** Consolidates calls to each slider drawing method into one method. */
  void DrawSliders();

  /** Draws the people number slider and its drag box. */
  void DrawPeopleSlider();

  /** Draws the incubation duration slider and its drag box. */
  void DrawIncubationSlider();

  /** Draws the speed slider and its drag box. */
  void DrawSpeedSlider();

  /** Draws the infection duration slider and its drag box. */
  void DrawInfectionSlider();

  /** Draws the contagiousness slider and its drag box. */
  void DrawContagiousnessSlider();

  /** Draws the play and reset buttons. */
  void DrawButtons();

  /**
   * Replaces simulator_ with a new instance that has the parameters specified
   * by the sliders.
   */
  void CheckResetButton(const glm::vec2& location);

  /** Window and speed */
  constexpr static float kSpeed = 33;
  constexpr static double kWindowWidth = 1400;
  constexpr static double kWindowHeight = 1000;

  /** Arena */
  constexpr static float kPersonRadius = 4;
  constexpr static float kArenaRadius = 330;
  const glm::vec2 kArenaCenter = glm::vec2(375, 650);

  /** Graph */
  std::vector<LocatedLabel> vertical_labels_;
  const glm::vec2 kGraphTopLeft = glm::vec2(880, 360);
  constexpr static double kGraphWidth = 500;
  constexpr static double kGraphHeight = 500;
  constexpr static double kVerticalLabelIntervalFactor = 5.0;
  const static size_t kInitialHorizontalLabelInterval = 1;
  constexpr static float kAxisLabelSize = 20.0f;
  const glm::vec2 kVerticalAxisNameLocation = glm::vec2(800, 600);
  const glm::vec2 kHorizontalAxisNameLocation = glm::vec2(1130, 880);
  constexpr static float kAxisNameSize = 35.0f;

  /** Text */
  const std::string kFont = "helvetica";
  const ci::Color kWhite = ci::Color("white");
  const ci::Color kBlack = ci::Color("black");

  /** Legend */
  const glm::vec2 kLegendTopLeft = glm::vec2(975, 100);
  const glm::vec2 kLegendBottomRight = glm::vec2(1240, 300);
  constexpr static float kLegendIconSize = 15;
  constexpr static float kLegendTextSize = 35.0f;
  constexpr static double kLegendMargin = 15;
  const glm::vec2 kFrequencyTopLeft = glm::vec2(1225, 100);

  /** Status colors */
  const ci::Color kVulnerableColor = ci::Color("gray");
  const ci::Color kIncubatingColor = ci::Color("orange");
  const ci::Color kInfectiousColor = ci::Color("red");
  const ci::Color kImmuneColor = ci::Color("green");

  /** Sliders */
  const ci::Color kSliderColor = ci::Color("gray");
  constexpr static double kSliderWidth = 150;
  constexpr static float kSliderTextSize = 30;
  constexpr static double kSliderHeight = 35;
  constexpr static double kDragBoxWidth = 25;

  /** People slider */
  Slider people_slider_;
  const glm::vec2 kPeopleSliderTopLeft = glm::vec2(275, 85);
  const static size_t kMinNumberPeople = 1;
  const static size_t kMaxNumberPeople = 1000;

  /** Incubation slider */
  Slider incubation_slider_;
  const glm::vec2 kIncubationSliderTopLeft = glm::vec2(550, 85);
  const static size_t kMinIncubation = 0;
  const static size_t kMaxIncubation = 20;

  /** Infection slider */
  Slider infection_slider_;
  const glm::vec2 kInfectionSliderTopLeft = glm::vec2(550, 200);
  const static size_t kMinInfection = 1;
  const static size_t kMaxInfection = 20;

  /** Contagiousness slider */
  Slider contagiousness_slider_;
  const glm::vec2 kContagiousnessSliderTopLeft = glm::vec2(275, 200);
  const static size_t kMinContagiousness = 0;
  const static size_t kMaxContagiousness = 100;

  /** Speed Slider */
  Slider speed_slider_;
  const glm::vec2 kSpeedSliderTopLeft = glm::vec2(780, 85);
  // The following constants are used as a base raised to an exponent for speed
  // calculations for a more user-friendly slider.
  constexpr static float kMinSpeedExponent = 1;
  constexpr static float kMaxSpeedExponent = 134;
  constexpr static double kSpeedBase = 1.05;

  /** Buttons */
  constexpr static float kButtonTextSize = 45;

  /** Play button */
  const glm::vec2 kPlayButtonTopLeft = glm::vec2(30, 30);
  const glm::vec2 kPlayButtonBottomRight = glm::vec2(200, 200);
  const ci::Color kPlayButtonColor = ci::Color("Green");
  const glm::vec2 kPlayButtonTextLocation =
      (kPlayButtonTopLeft + kPlayButtonBottomRight) * 0.5f -
      glm::vec2(0, kButtonTextSize / 3);
  Button play_button_;

  /** Reset button */
  const glm::vec2 kResetButtonTopLeft = glm::vec2(30, 210);
  const glm::vec2 kResetButtonBottomRight = glm::vec2(200, 320);
  const ci::Color kResetButtonColor = ci::Color("Red");
  const glm::vec2 kResetButtonTextLocationSettings =
      (kResetButtonTopLeft + kResetButtonBottomRight) * 0.5f +
      glm::vec2(0, kButtonTextSize / 4);
  const glm::vec2 kResetButtonTextLocationApply =
      (kResetButtonTopLeft + kResetButtonBottomRight) * 0.5f -
      glm::vec2(0, 0.75 * kButtonTextSize);
  Button reset_button_;

  /** Simulator instance */
  epidemic_simulator::Simulator simulator_;
};
}  // namespace visualizer
}  // namespace epidemic_simulator

#endif  // FINAL_PROJECT_JLIVSHOTS_EPIDEMIC_APP_H