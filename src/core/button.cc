#include "core/button.h"
namespace epidemic_simulator {

Button::Button(const glm::vec2& bottom_right_corner)
    : is_playing_(false),
      width_(bottom_right_corner.x),
      height_(bottom_right_corner.y) {
}
}  // namespace epidemic_simulator