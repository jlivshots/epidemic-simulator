#ifndef EPIDEMIC_SIMULATOR_BUTTON_H
#define EPIDEMIC_SIMULATOR_BUTTON_H

#include "cinder/gl/gl.h"

namespace epidemic_simulator {
/**
 * Button class allows a user to press a rectangular button to pause/play.
 */
class Button {
 public:
  /**
   * Instantiates a new Button Object. Assumes top left corner of button is
   * (0,0).
   * @param bottom_right_corner the bottom right corner of the button.
   * is_playing_ is set to false by default.
   */
  explicit Button(const glm::vec2& bottom_right_corner);

  /**
   * Returns true if the button has been clicked, false otherwise. If the button
   * has been clicked, is_playing_ is inverted.
   * @param mouse_location the location of the mouse.
   * @return a bool representing if the button has been clicked.
   */
  bool ClickMouse(const glm::vec2& mouse_location);

  void SetPlayingStatus(bool is_playing);

  bool IsPlaying() const;

 private:
  bool is_playing_;
  double width_;
  double height_;
};
}  // namespace epidemic_simulator

#endif  // EPIDEMIC_SIMULATOR_BUTTON_H