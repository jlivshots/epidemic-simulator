#include "visualizer/epidemic_app.h"

namespace epidemic_simulator {
namespace visualizer {

EpidemicSimulatorApp::EpidemicSimulatorApp()
    : simulator_(kNumberPeople, kArenaRadius, kSpeed, kVirus) {
  ci::app::setWindowSize((int)kWindowWidth, (int)kWindowHeight);
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
    SetStatusColor(person.GetStatus());
    ci::gl::drawSolidCircle(kArenaCenter + person.GetLocation(), kPersonRadius);
  }

  const std::vector<ColumnStatus> bars = simulator_.GetBars();
  for (const ColumnStatus& column_status : bars) {
    SetStatusColor(column_status.first);
    ci::Rectf rectangle = column_status.second;
    ci::Rectf moved_rectangle(glm::vec2(rectangle.x1 + kGraphTopLeft.x,
                                        rectangle.y1 + kGraphTopLeft.y),
                              glm::vec2(rectangle.x2 + kGraphTopLeft.x,
                                        rectangle.y2 + kGraphTopLeft.y));
    ci::gl::drawSolidRect(moved_rectangle);
  }
}

void EpidemicSimulatorApp::SetStatusColor(Status status) {
  switch (status) {
    case Status::Vulnerable:
      ci::gl::color(kVulnerableColor);
      break;
    case Status::Incubating:
      ci::gl::color(kIncubatingColor);
      break;
    case Status::Infectious:
      ci::gl::color(kInfectiousColor);
      break;
    case Status::Immune:
      ci::gl::color(kImmuneColor);
      break;
  }
}
}  // namespace visualizer
}  // namespace epidemic_simulator