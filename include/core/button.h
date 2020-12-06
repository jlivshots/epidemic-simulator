#ifndef EPIDEMIC_SIMULATOR_BUTTON_H
#define EPIDEMIC_SIMULATOR_BUTTON_H

#include "cinder/gl/gl.h"

namespace epidemic_simulator {
/**
 * Button class allows a user to press a button to pause/play.
 */
class Button {
 public:

  Button(const glm::vec2& bottom_right_corner);


  bool ClickMouse(const glm::vec2& mouse_location);

 private:
  bool is_playing_;
  double width_;
  double height_;
};
}  // namespace epidemic_simulator
#endif  // EPIDEMIC_SIMULATOR_BUTTON_H
