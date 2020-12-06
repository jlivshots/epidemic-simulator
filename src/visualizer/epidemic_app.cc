#include "visualizer/epidemic_app.h"

namespace epidemic_simulator {
namespace visualizer {

EpidemicSimulatorApp::EpidemicSimulatorApp()
    : simulator_(kNumberPeople, kArenaRadius, kSpeed, kVirus, kGraphWidth,
                 kGraphHeight, kVerticalLabelInterval,
                 kInitialHorizontalLabelInterval),
      people_slider_(kMinNumberPeople, kMaxNumberPeople, kDragBoxWidth,
                     glm::vec2(kSliderWidth, kSliderHeight)),
      play_button_(kPlayButtonBottomRight - kPlayButtonTopLeft) {
  ci::app::setWindowSize((int)kWindowWidth, (int)kWindowHeight);
  vertical_labels_ = simulator_.GetVerticalLabels();
  simulator_.ShufflePeople();
}

void EpidemicSimulatorApp::draw() {
  //  simulator_= Simulator(kNumberPeople, kArenaRadius, kSpeed, kVirus,
  //  kGraphWidth,
  //                        kGraphHeight, kVerticalLabelInterval,
  //                        kInitialHorizontalLabelInterval);
  ci::Color8u background_color(ci::Color("black"));
  ci::gl::clear(background_color);
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedCircle(kArenaCenter, kArenaRadius);

  simulator_.PerformNextFrame();
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

void EpidemicSimulatorApp::DrawLegend() {
  ci::Rectf boundary(kLegendTopLeft, kLegendBottomRight);
  ci::gl::color(ci::Color("white"));
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
        kTextColor, ci::Font(kFont, kLegendTextSize));

    ci::gl::drawStringRight(
        std::to_string(iterator.second),
        kFrequencyTopLeft + glm::vec2(0, kLegendMargin + entry_height * index),
        kTextColor, ci::Font(kFont, kLegendTextSize));
    ++index;
  }
}

void EpidemicSimulatorApp::DrawVerticalAxis() {
  for (const LocatedLabel& label : vertical_labels_) {
    ci::gl::drawStringRight(std::to_string(label.first),
                            kGraphTopLeft + label.second, kTextColor,
                            ci::Font(kFont, kAxisLabelSize));
  }
  ci::gl::pushModelMatrix();
  ci::gl::translate(kVerticalAxisNameLocation);
  ci::gl::rotate((float)-M_PI / 2);
  ci::gl::drawStringCentered("Number of People", glm::vec2(0, 0), kTextColor,
                             ci::Font(kFont, kAxisNameSize));
  ci::gl::popModelMatrix();
}

void EpidemicSimulatorApp::DrawHorizontalAxis() {
  std::vector<LocatedLabel> horizontal_labels_ =
      simulator_.GetHorizontalLabels();
  for (const LocatedLabel& label : horizontal_labels_) {
    ci::gl::drawStringRight(
        std::to_string(label.first),
        kGraphTopLeft + glm::vec2(0, kGraphHeight) + label.second, kTextColor,
        ci::Font(kFont, kAxisLabelSize));
  }
  ci::gl::drawStringCentered("Day", kHorizontalAxisNameLocation, kTextColor,
                             ci::Font(kFont, kAxisNameSize));
}

void EpidemicSimulatorApp::mouseDown(ci::app::MouseEvent event) {
  glm::vec2 current_location = event.getPos();
  people_slider_.BeginDragging(current_location - kPeopleSliderTopLeft);
  play_button_.ClickMouse(current_location - kPlayButtonTopLeft);
}

void EpidemicSimulatorApp::mouseUp(ci::app::MouseEvent event) {
  people_slider_.StopDragging();
}
void EpidemicSimulatorApp::mouseDrag(ci::app::MouseEvent event) {
  glm::vec2 current_location = event.getPos();
  people_slider_.UpdateSlider(current_location - kPeopleSliderTopLeft);
}

void EpidemicSimulatorApp::DrawSliders() {
  ci::Rectf boundary(
      kPeopleSliderTopLeft,
      kPeopleSliderTopLeft + glm::vec2(kSliderWidth, kSliderHeight));
  ci::gl::color(ci::Color(kSliderColor));
  ci::gl::drawStrokedRect(boundary);

  ci::gl::drawStringRight(std::to_string(kMinNumberPeople),
                          kPeopleSliderTopLeft, kTextColor,
                          ci::Font(kFont, kSliderTextSize));

  ci::gl::drawString(std::to_string(kMaxNumberPeople),
                     kPeopleSliderTopLeft + glm::vec2(kSliderWidth, 0),
                     kTextColor, ci::Font(kFont, kSliderTextSize));
  ci::gl::drawString(
      "People: " + std::to_string((int)people_slider_.GetValue()),
      kPeopleSliderTopLeft + glm::vec2(0, -kSliderHeight), kTextColor,
      ci::Font(kFont, kSliderTextSize));
  ci::Rectf people_drag_box = people_slider_.GenerateDragBox();
  ci::gl::drawSolidRect(people_drag_box + kPeopleSliderTopLeft);
}

void EpidemicSimulatorApp::DrawButtons() {
  ci::gl::color(ci::Color(kPlayButtonColor));
  ci::Rectf play_boundary(kPlayButtonTopLeft, kPlayButtonBottomRight);
  ci::gl::drawSolidRect(play_boundary);
  std::string play_label;
  if (play_button_.IsPlaying()) {
    play_label = "PAUSE";
  } else {
    play_label = "RUN";
  }
  ci::gl::drawStringCentered(
      play_label, (kPlayButtonTopLeft + kPlayButtonBottomRight).operator*=(0.5),
      kTextColor, ci::Font(kFont, kButtonTextSize));
}

}  // namespace visualizer
}  // namespace epidemic_simulator