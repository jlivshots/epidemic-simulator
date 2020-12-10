#include "visualizer/epidemic_app.h"

namespace epidemic_simulator {
namespace visualizer {

EpidemicSimulatorApp::EpidemicSimulatorApp()
    : simulator_(kMinNumberPeople, kArenaRadius, kSpeed,
                 Virus((double)kMinContagiousness / 100, (size_t)kMinIncubation,
                       (size_t)kMinInfection),
                 kGraphWidth, kGraphHeight, kMinNumberPeople,
                 kInitialHorizontalLabelInterval),
      people_slider_(kMinNumberPeople, kMaxNumberPeople, kDragBoxWidth,
                     glm::vec2(kSliderWidth, kSliderHeight)),
      incubation_slider_(kMinIncubation, kMaxIncubation, kDragBoxWidth,
                         glm::vec2(kSliderWidth, kSliderHeight)),
      infection_slider_(kMinInfection, kMaxInfection, kDragBoxWidth,
                        glm::vec2(kSliderWidth, kSliderHeight)),
      contagiousness_slider_(kMinContagiousness, kMaxContagiousness,
                             kDragBoxWidth,
                             glm::vec2(kSliderWidth, kSliderHeight)),
      speed_slider_(kMinSpeedExponent, kMaxSpeedExponent, kDragBoxWidth,
                    glm::vec2(kSliderWidth, kSliderHeight)),
      play_button_(kPlayButtonBottomRight - kPlayButtonTopLeft),
      reset_button_(kResetButtonBottomRight - kResetButtonTopLeft) {
  ci::app::setWindowSize((int)kWindowWidth, (int)kWindowHeight);
  vertical_labels_ = simulator_.GetVerticalLabels();
}

void EpidemicSimulatorApp::draw() {
  ci::gl::clear(kBlack);
  ci::gl::color(ci::Color(kWhite));
  ci::gl::drawStrokedCircle(kArenaCenter, kArenaRadius);
  if (play_button_.IsPlaying()) {
    simulator_.SetSpeed((float)std::pow(kSpeedBase, speed_slider_.GetValue()));
    simulator_.PerformNextFrame();
  }

  const std::vector<Person> people = simulator_.GetPeople();
  for (const Person& person : people) {
    SetColorAndGetName(person.GetStatus());
    ci::gl::drawSolidCircle(kArenaCenter + person.GetLocation(), kPersonRadius);
  }

  const std::vector<ColumnStatus> bars = simulator_.GetBars();
  for (const ColumnStatus& column_status : bars) {
    SetColorAndGetName(column_status.first);
    ci::Rectf rectangle = column_status.second;
    ci::Rectf moved_rectangle(glm::vec2(rectangle.x1 + kGraphTopLeft.x,
                                        rectangle.y1 + kGraphTopLeft.y),
                              glm::vec2(rectangle.x2 + kGraphTopLeft.x,
                                        rectangle.y2 + kGraphTopLeft.y));
    ci::gl::drawSolidRect(moved_rectangle);
  }
  DrawLegend();
  DrawVerticalAxis();
  DrawHorizontalAxis();
  DrawSliders();
  DrawButtons();
}

void EpidemicSimulatorApp::mouseDown(ci::app::MouseEvent event) {
  glm::vec2 current_location = event.getPos();
  people_slider_.BeginDragging(current_location - kPeopleSliderTopLeft);
  incubation_slider_.BeginDragging(current_location - kIncubationSliderTopLeft);
  infection_slider_.BeginDragging(current_location - kInfectionSliderTopLeft);
  contagiousness_slider_.BeginDragging(current_location -
                                       kContagiousnessSliderTopLeft);
  speed_slider_.BeginDragging(current_location - kSpeedSliderTopLeft);
  play_button_.ClickMouse(current_location - kPlayButtonTopLeft);
  CheckResetButton(current_location);
}

void EpidemicSimulatorApp::mouseUp(ci::app::MouseEvent event) {
  people_slider_.StopDragging();
  incubation_slider_.StopDragging();
  infection_slider_.StopDragging();
  contagiousness_slider_.StopDragging();
  speed_slider_.StopDragging();
}

void EpidemicSimulatorApp::mouseDrag(ci::app::MouseEvent event) {
  glm::vec2 current_location = event.getPos();
  people_slider_.UpdateSlider(current_location - kPeopleSliderTopLeft);
  incubation_slider_.UpdateSlider(current_location - kIncubationSliderTopLeft);
  infection_slider_.UpdateSlider(current_location - kInfectionSliderTopLeft);
  contagiousness_slider_.UpdateSlider(current_location -
                                      kContagiousnessSliderTopLeft);
  speed_slider_.UpdateSlider(current_location - kSpeedSliderTopLeft);
}

std::string EpidemicSimulatorApp::SetColorAndGetName(
    const Status& status) const {
  std::string status_string;
  switch (status) {
    case Status::Vulnerable:
      ci::gl::color(kVulnerableColor);
      status_string = "Vulnerable";
      break;
    case Status::Incubating:
      ci::gl::color(kIncubatingColor);
      status_string = "Incubating";
      break;
    case Status::Infectious:
      ci::gl::color(kInfectiousColor);
      status_string = "Infectious";
      break;
    case Status::Immune:
      ci::gl::color(kImmuneColor);
      status_string = "Immune";
      break;
  }
  return status_string;
}

void EpidemicSimulatorApp::DrawLegend() const {
  ci::Rectf boundary(kLegendTopLeft, kLegendBottomRight);
  ci::gl::color(kWhite);
  ci::gl::drawStrokedRect(boundary);

  std::map<Status, size_t> frequencies = simulator_.GetFrequencies();
  double height = (kLegendBottomRight.y - kLegendTopLeft.y) - 2 * kLegendMargin;
  double entry_height = height / frequencies.size();
  size_t index = 0;
  for (auto& iterator : frequencies) {
    std::string label = SetColorAndGetName(iterator.first);
    ci::gl::drawSolidCircle(
        kLegendTopLeft +
            glm::vec2(kLegendIconSize + kLegendMargin,
                      kLegendMargin + entry_height * index + kLegendIconSize),
        kLegendIconSize);
    ci::gl::drawString(
        label,
        kLegendTopLeft + glm::vec2(2 * kLegendIconSize + 2 * kLegendMargin,
                                   kLegendMargin + entry_height * index),
        kWhite, ci::Font(kFont, kLegendTextSize));

    ci::gl::drawStringRight(
        std::to_string(iterator.second),
        kFrequencyTopLeft + glm::vec2(0, kLegendMargin + entry_height * index),
        kWhite, ci::Font(kFont, kLegendTextSize));
    ++index;
  }
}

void EpidemicSimulatorApp::DrawVerticalAxis() const {
  for (const LocatedLabel& label : vertical_labels_) {
    ci::gl::drawStringRight(std::to_string(label.first),
                            kGraphTopLeft + label.second, kWhite,
                            ci::Font(kFont, kAxisLabelSize));
  }
  ci::gl::ScopedModelMatrix scoped_matrix;
  ci::gl::translate(kVerticalAxisNameLocation);
  ci::gl::rotate((float)-M_PI / 2);
  ci::gl::drawStringCentered("Number of People", glm::vec2(0, 0), kWhite,
                             ci::Font(kFont, kAxisNameSize));
}

void EpidemicSimulatorApp::DrawHorizontalAxis() const {
  std::vector<LocatedLabel> horizontal_labels_ =
      simulator_.GetHorizontalLabels();
  for (const LocatedLabel& label : horizontal_labels_) {
    ci::gl::drawStringRight(
        std::to_string(label.first),
        kGraphTopLeft + glm::vec2(0, kGraphHeight) + label.second, kWhite,
        ci::Font(kFont, kAxisLabelSize));
  }
  ci::gl::drawStringCentered("Day", kHorizontalAxisNameLocation, kWhite,
                             ci::Font(kFont, kAxisNameSize));
}

void EpidemicSimulatorApp::DrawSliders() const {
  DrawPeopleSlider();
  DrawIncubationSlider();
  DrawInfectionSlider();
  DrawContagiousnessSlider();
  DrawSpeedSlider();
}

void EpidemicSimulatorApp::DrawButtons() const {
  ci::gl::color(ci::Color(kPlayButtonColor));
  ci::Rectf play_boundary(kPlayButtonTopLeft, kPlayButtonBottomRight);
  ci::gl::drawSolidRect(play_boundary);
  std::string play_label;
  if (play_button_.IsPlaying()) {
    play_label = "PAUSE";
  } else {
    play_label = "RUN";
  }
  ci::gl::drawStringCentered(play_label, kPlayButtonTextLocation, kWhite,
                             ci::Font(kFont, kButtonTextSize));

  ci::gl::color(ci::Color(kResetButtonColor));
  ci::Rectf reset_boundary(kResetButtonTopLeft, kResetButtonBottomRight);
  ci::gl::drawSolidRect(reset_boundary);
  ci::gl::drawStringCentered("APPLY", kResetButtonTextLocationApply, kWhite,
                             ci::Font(kFont, kButtonTextSize));
  ci::gl::drawStringCentered("SETTINGS", kResetButtonTextLocationSettings,
                             kWhite, ci::Font(kFont, kButtonTextSize));
}

void EpidemicSimulatorApp::DrawPeopleSlider() const {
  ci::Rectf boundary(
      kPeopleSliderTopLeft,
      kPeopleSliderTopLeft + glm::vec2(kSliderWidth, kSliderHeight));
  ci::gl::color(ci::Color(kSliderColor));
  ci::gl::drawStrokedRect(boundary);
  ci::gl::drawStringRight(std::to_string(kMinNumberPeople),
                          kPeopleSliderTopLeft, kWhite,
                          ci::Font(kFont, kSliderTextSize));
  ci::gl::drawString(std::to_string(kMaxNumberPeople),
                     kPeopleSliderTopLeft + glm::vec2(kSliderWidth, 0), kWhite,
                     ci::Font(kFont, kSliderTextSize));
  ci::gl::drawStringCentered(
      "People: " + std::to_string((int)people_slider_.GetValue()),
      kPeopleSliderTopLeft + glm::vec2(kSliderWidth / 2, -kSliderHeight),
      kWhite, ci::Font(kFont, kSliderTextSize));
  ci::Rectf people_drag_box = people_slider_.GenerateDragBox();
  ci::gl::drawSolidRect(people_drag_box + kPeopleSliderTopLeft);
}

void EpidemicSimulatorApp::DrawIncubationSlider() const {
  ci::Rectf boundary(
      kIncubationSliderTopLeft,
      kIncubationSliderTopLeft + glm::vec2(kSliderWidth, kSliderHeight));
  ci::gl::color(ci::Color(kSliderColor));
  ci::gl::drawStrokedRect(boundary);
  ci::gl::drawStringRight(std::to_string(kMinIncubation),
                          kIncubationSliderTopLeft, kWhite,
                          ci::Font(kFont, kSliderTextSize));
  ci::gl::drawString(std::to_string(kMaxIncubation),
                     kIncubationSliderTopLeft + glm::vec2(kSliderWidth, 0),
                     kWhite, ci::Font(kFont, kSliderTextSize));
  ci::gl::drawStringCentered(
      "Incubation Days: " + std::to_string((int)incubation_slider_.GetValue()),
      kIncubationSliderTopLeft + glm::vec2(kSliderWidth / 2, -kSliderHeight),
      kWhite, ci::Font(kFont, kSliderTextSize));
  ci::Rectf incubation_drag_box = incubation_slider_.GenerateDragBox();
  ci::gl::drawSolidRect(incubation_drag_box + kIncubationSliderTopLeft);
}

void EpidemicSimulatorApp::DrawInfectionSlider() const {
  ci::Rectf boundary(
      kInfectionSliderTopLeft,
      kInfectionSliderTopLeft + glm::vec2(kSliderWidth, kSliderHeight));
  ci::gl::color(ci::Color(kSliderColor));
  ci::gl::drawStrokedRect(boundary);
  ci::gl::drawStringRight(std::to_string(kMinInfection),
                          kInfectionSliderTopLeft, kWhite,
                          ci::Font(kFont, kSliderTextSize));
  ci::gl::drawString(std::to_string(kMaxInfection),
                     kInfectionSliderTopLeft + glm::vec2(kSliderWidth, 0),
                     kWhite, ci::Font(kFont, kSliderTextSize));
  ci::gl::drawStringCentered(
      "Infectious Days: " + std::to_string((int)infection_slider_.GetValue()),
      kInfectionSliderTopLeft + glm::vec2(kSliderWidth / 2, -kSliderHeight),
      kWhite, ci::Font(kFont, kSliderTextSize));
  ci::Rectf infection_drag_box = infection_slider_.GenerateDragBox();
  ci::gl::drawSolidRect(infection_drag_box + kInfectionSliderTopLeft);
}

void EpidemicSimulatorApp::DrawContagiousnessSlider() const {
  ci::Rectf boundary(
      kContagiousnessSliderTopLeft,
      kContagiousnessSliderTopLeft + glm::vec2(kSliderWidth, kSliderHeight));
  ci::gl::color(ci::Color(kSliderColor));
  ci::gl::drawStrokedRect(boundary);
  ci::gl::drawStringRight(std::to_string(kMinContagiousness) + "%",
                          kContagiousnessSliderTopLeft, kWhite,
                          ci::Font(kFont, kSliderTextSize));
  ci::gl::drawString(std::to_string(kMaxContagiousness) + "%",
                     kContagiousnessSliderTopLeft + glm::vec2(kSliderWidth, 0),
                     kWhite, ci::Font(kFont, kSliderTextSize));
  ci::gl::drawStringCentered(
      "Infection Rate: " +
          std::to_string((int)contagiousness_slider_.GetValue()) + "%",
      kContagiousnessSliderTopLeft +
          glm::vec2(kSliderWidth / 2, -kSliderHeight),
      kWhite, ci::Font(kFont, kSliderTextSize));
  ci::Rectf contagiousness_drag_box = contagiousness_slider_.GenerateDragBox();
  ci::gl::drawSolidRect(contagiousness_drag_box + kContagiousnessSliderTopLeft);
}

void EpidemicSimulatorApp::DrawSpeedSlider() const {
  ci::Rectf boundary(
      kSpeedSliderTopLeft,
      kSpeedSliderTopLeft + glm::vec2(kSliderWidth, kSliderHeight));
  ci::gl::color(ci::Color(kSliderColor));
  ci::gl::drawStrokedRect(boundary);
  ci::gl::drawStringCentered(
      "Speed",
      kSpeedSliderTopLeft + glm::vec2(kSliderWidth / 2, -kSliderHeight), kWhite,
      ci::Font(kFont, kSliderTextSize));
  ci::Rectf speed_drag_box = speed_slider_.GenerateDragBox();
  ci::gl::drawSolidRect(speed_drag_box + kSpeedSliderTopLeft);
}

void EpidemicSimulatorApp::CheckResetButton(const glm::vec2& current_location) {
  if (reset_button_.ClickMouse(current_location - kResetButtonTopLeft)) {
    double vertical_interval =
        std::max(1.0, people_slider_.GetValue() / kVerticalLabelIntervalFactor);
    simulator_ =
        Simulator((size_t)people_slider_.GetValue(), kArenaRadius, kSpeed,
                  Virus(contagiousness_slider_.GetValue() / 100,
                        (size_t)incubation_slider_.GetValue(),
                        (size_t)infection_slider_.GetValue()),
                  kGraphWidth, kGraphHeight, (size_t)vertical_interval,
                  kInitialHorizontalLabelInterval);
    vertical_labels_ = simulator_.GetVerticalLabels();
    play_button_.SetPlayingStatus(false);
  }
}
}  // namespace visualizer
}  // namespace epidemic_simulator