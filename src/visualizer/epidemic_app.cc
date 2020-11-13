#include "visualizer/epidemic_app.h"

namespace epidemic_simulator {
namespace visualizer {

EpidemicSimulatorApp::EpidemicSimulatorApp()
    : simulator_(kNumberPeople, kArenaRadius),
      person_(glm::vec2(350, 500)),
      target_(glm::vec2(900, 900)) {
  ci::app::setWindowSize((int)kWindowWidth, (int)kWindowHeight);
}

void EpidemicSimulatorApp::draw() {
  ci::Color8u background_color(ci::Color("black"));
  ci::gl::clear(background_color);
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedCircle(kArenaCenter, kArenaRadius);

  //  if(person_.MoveTowardLocation(target_, 10.1f)) {
  //    target_ = glm::vec2(20, 50);
  //  }
  //  ci::gl::drawSolidCircle( person_.GetLocation(), 3);

  std::vector<Person> people = simulator_.GetPeople();
  for (const Person& person : people) {
    ci::gl::drawSolidCircle(kArenaCenter + person.GetLocation(), kPersonSize);
  }
}
}  // namespace visualizer
}  // namespace epidemic_simulator