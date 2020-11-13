#include "visualizer/epidemic_app.h"

namespace epidemic_simulator {
namespace visualizer {

EpidemicSimulatorApp::EpidemicSimulatorApp(): simulator_(kNumberPeople, kArenaRadius), person_(glm::vec2(350,500)) {
  ci::app::setWindowSize((int)kWindowWidth, (int)kWindowHeight);
}

void EpidemicSimulatorApp::draw() {
  ci::Color8u background_color(ci::Color("black"));
  ci::gl::clear(background_color);
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedCircle(kArenaCenter , kArenaRadius);

  person_.MoveTowardLocation(glm::vec2(50, 20), 10.1f);
  ci::gl::drawSolidCircle( person_.GetLocation(), 10);

}
}  // namespace visualizer
}  // namespace epidemic_simulator