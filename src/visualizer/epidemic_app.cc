#include "visualizer/epidemic_app.h"

namespace epidemic_simulator {
namespace visualizer {

EpidemicSimulatorApp::EpidemicSimulatorApp()
    : simulator_(kNumberPeople, kArenaRadius, kSpeed, kVirus, kGraphWidth,
                 kGraphHeight, kVerticalLabelInterval,
                 kHorizontalLabelInterval) {
  ci::app::setWindowSize((int)kWindowWidth, (int)kWindowHeight);
  vertical_labels_ = simulator_.GetVerticalLabels();
  simulator_.ShufflePeople();
}

void EpidemicSimulatorApp::draw() {
  ci::Color8u background_color(ci::Color("black"));
  ci::gl::clear(background_color);
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedCircle(kArenaCenter, kArenaRadius);

  simulator_.PerformNextFrame();
  const std::vector<Person> people = simulator_.GetPeople();

  for (const Person& person : people) {
    SetAndGetColorFromStatus(person.GetStatus());
    ci::gl::drawSolidCircle(kArenaCenter + person.GetLocation(), kPersonRadius);
  }

  const std::vector<ColumnStatus> bars = simulator_.GetBars();
  for (const ColumnStatus& column_status : bars) {
    SetAndGetColorFromStatus(column_status.first);
    ci::Rectf rectangle = column_status.second;
    ci::Rectf moved_rectangle(glm::vec2(rectangle.x1 + kGraphTopLeft.x,
                                        rectangle.y1 + kGraphTopLeft.y),
                              glm::vec2(rectangle.x2 + kGraphTopLeft.x,
                                        rectangle.y2 + kGraphTopLeft.y));
    ci::gl::drawSolidRect(moved_rectangle);
  }
  DrawLegend();
  DrawVerticalAxis();
}

std::string EpidemicSimulatorApp::SetAndGetColorFromStatus(
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
  for (auto iterator : frequencies) {
    std::string label = SetAndGetColorFromStatus(iterator.first);
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
  ci::gl::drawStringCentered("Number of People", glm::vec2(0, 0),
                             kTextColor, ci::Font(kFont, kAxisNameSize));
  ci::gl::popModelMatrix();
}

}  // namespace visualizer
}  // namespace epidemic_simulator