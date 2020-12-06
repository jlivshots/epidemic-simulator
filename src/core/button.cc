#include "core/button.h"
namespace epidemic_simulator {

Button::Button(const glm::vec2& bottom_right_corner)
    : is_playing_(false),
      width_(bottom_right_corner.x),
      height_(bottom_right_corner.y) {
}

bool Button::ClickMouse(const glm::vec2& mouse_location) {
  double mouse_x = mouse_location.x;
  double mouse_y = mouse_location.y;
  bool is_clicked =
      (mouse_x >= 0 && mouse_x <= width_ && mouse_y >= 0 && mouse_y <= height_);
  if (is_clicked) {
    is_playing_ = !is_playing_;
  }
  return is_clicked;
}

bool Button::IsPlaying() const{
  return is_playing_;
}

void Button::SetPlayingStatus(bool is_playing) {
  is_playing_ = is_playing;
}
}  // namespace epidemic_simulator