#include <core/slider.h>

namespace epidemic_simulator {
epidemic_simulator::Slider::Slider(double min_value, double max_value,
                                   float drag_box_width,
                                   glm::vec2& bottom_right_corner)
    : slider_height_(bottom_right_corner.y),
      sliding_width_(bottom_right_corner.x - drag_box_width),
      current_value_(min_value),
      drag_box_left_(0),
      drag_box_right(drag_box_width),
      is_dragged_(false) {
}
}  // namespace epidemic_simulator