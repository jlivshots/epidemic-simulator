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
  std::vector<Person> people = simulator_.GetPeople();

  for (const Person& person : people) {
    SetStatusColor(person.GetStatus());
    ci::gl::drawSolidCircle(kArenaCenter + person.GetLocation(), kPersonRadius);
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