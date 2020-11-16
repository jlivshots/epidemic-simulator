#ifndef FINAL_PROJECT_JLIVSHOTS_EPIDEMIC_APP_H
#define FINAL_PROJECT_JLIVSHOTS_EPIDEMIC_APP_H


#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "core/simulator.h"
#include "core/person.h"
#include "core/virus.h"

namespace epidemic_simulator {
namespace visualizer {
class EpidemicSimulatorApp : public ci::app::App {
 public:
  EpidemicSimulatorApp();

  void draw() override;

 private:
  const size_t kNumberPeople = 601;
  const float kArenaRadius = 400;
  const float kSpeed = 11;
  const glm::vec2 kArenaCenter = glm::vec2(400,500);
  const float kPersonSize = 5;
  const Virus kVirus = Virus(0.9, 2, 5);

  const double kWindowWidth = 1400;
  const double kWindowHeight = 1000;
  epidemic_simulator::Simulator simulator_;


};
}
}




#endif //FINAL_PROJECT_JLIVSHOTS_EPIDEMIC_APP_H
