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
  const size_t kNumberPeople = 300;
  const float kArenaRadius = 400;
  const float kSpeed = 9;
  const glm::vec2 kArenaCenter = glm::vec2(400,500);
  const float kPersonSize = 4;
  const Virus kVirus = Virus(0.39, 1, 2);

  const double kWindowWidth = 1400;
  const double kWindowHeight = 1000;
  const ci::Color kVulnerableColor = ci::Color("white");
  const ci::Color kIncubatingColor = ci::Color("orange");
  const ci::Color kInfectiousColor = ci::Color("red");
  const ci::Color kImmuneColor = ci::Color("green");

  epidemic_simulator::Simulator simulator_;


};
}
}




#endif //FINAL_PROJECT_JLIVSHOTS_EPIDEMIC_APP_H
