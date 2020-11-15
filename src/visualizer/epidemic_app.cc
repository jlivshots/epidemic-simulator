#include "visualizer/epidemic_app.h"

namespace epidemic_simulator {
namespace visualizer {

EpidemicSimulatorApp::EpidemicSimulatorApp()
    : simulator_(kNumberPeople, kArenaRadius),
      person_(glm::vec2(0, 0)),
      target_(glm::vec2(900, 900)) {
  ci::app::setWindowSize((int)kWindowWidth, (int)kWindowHeight);
  simulator_.ShuffleSlots();
}

void EpidemicSimulatorApp::draw() {
  ++counter;
  ci::Color8u background_color(ci::Color("black"));
  ci::gl::clear(background_color);
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedCircle(kArenaCenter, kArenaRadius);
  ci::gl::color(ci::Color("yellow"));
if(simulator_.ApproachNewLocations()) {
  simulator_.ShuffleSlots();
}
    ci::gl::drawSolidCircle( person_.GetLocation(), 3);

  std::vector<Person> people = simulator_.GetPeople();


  for (Person& person : people) {
    ci::gl::drawSolidCircle(kArenaCenter + person.GetLocation(), kPersonSize);
  }
}
}  // namespace visualizer
}  // namespace epidemic_simulator