#ifndef FINAL_PROJECT_JLIVSHOTS_EPIDEMIC_APP_H
#define FINAL_PROJECT_JLIVSHOTS_EPIDEMIC_APP_H


#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "core/simulator.h"
#include "core/person.h"

namespace epidemic_simulator {
namespace visualizer {
class EpidemicSimulatorApp : public ci::app::App {
 public:
  EpidemicSimulatorApp();

  void draw() override;

 private:
  const size_t kNumberPeople = 5;
  const float kArenaRadius = 300;
  const glm::vec2 kArenaCenter = glm::vec2(350,500);
  const double kWindowWidth = 1400;
  const double kWindowHeight = 1000;
  epidemic_simulator::Simulator simulator_;
  Person person_;

};
}
}




#endif //FINAL_PROJECT_JLIVSHOTS_EPIDEMIC_APP_H
