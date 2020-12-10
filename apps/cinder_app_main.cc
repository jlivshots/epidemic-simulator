#include <visualizer/epidemic_app.h>

using epidemic_simulator::visualizer::EpidemicSimulatorApp;

void prepareSettings(EpidemicSimulatorApp::Settings* settings) {
  settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(EpidemicSimulatorApp, ci::app::RendererGl, prepareSettings);