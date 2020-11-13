#include "visualizer/epidemic_app.h"

namespace epidemic_simulator {
namespace visualizer {

EpidemicSimulatorApp::EpidemicSimulatorApp() {

}

void EpidemicSimulatorApp::draw() {
  ci::Color8u background_color(ci::Color("black"));
  ci::gl::clear(background_color);
  ci::gl::color(ci::Color::gray(0.3f));
}
}  // namespace visualizer
}  // namespace epidemic_simulator