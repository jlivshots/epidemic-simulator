#ifndef EPIDEMIC_SIMULATOR_BUTTON_H
#define EPIDEMIC_SIMULATOR_BUTTON_H

#include "cinder/gl/gl.h"

namespace epidemic_simulator {
/**
 * Button class allows a user to press a button to pause/play.
 */
class Button {
 public:
  /**
   * Instantiates a new Button Object. Assumes top left corner of button is
   * (0,0).
   * @param bottom_right_corner the bottom right corner of the button.
   * is_playing_ is set to false by default.
   */
  Button(const glm::vec2& bottom_right_corner);

  /**
   * Returns true if the button has been clicked, false otherwise.
   * @param mouse_location
   * @return
   */
  bool ClickMouse(const glm::vec2& mouse_location);

 private:
  bool is_playing_;
  double width_;
  double height_;
};
}  // namespace epidemic_simulator
#endif  // EPIDEMIC_SIMULATOR_BUTTON_H
