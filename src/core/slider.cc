#include <core/slider.h>

namespace epidemic_simulator {
epidemic_simulator::Slider::Slider(double min_value, double max_value,
                                   float drag_box_width,
                                   glm::vec2& bottom_right_corner)
    : drag_box_height_(bottom_right_corner.y),
      sliding_width_(bottom_right_corner.x - drag_box_width),
      current_value_(min_value),
      drag_box_left_(0),
      drag_box_right_(drag_box_width),
      is_dragged_(false),
      drag_box_width_(drag_box_width) {
}

std::pair<double, ci::Rectf> Slider::UpdateSlider(glm::vec2& mouse_position) {
  double half_drag_box_width = drag_box_width_ / 2;
  if (is_dragged_) {
    double mouse_x = mouse_position.x;
    if (mouse_x <= half_drag_box_width) {
      drag_box_left_ = 0;
      drag_box_right_ = drag_box_width_;
    } else if (mouse_x >= sliding_width_ + half_drag_box_width) {
      drag_box_left_ = sliding_width_;
      drag_box_right_ = sliding_width_ + drag_box_width_;
    } else {
      drag_box_left_ = mouse_x - half_drag_box_width;
      drag_box_right_ = mouse_x + half_drag_box_width;
    }
  }
  return std::make_pair(
      current_value_, ci::Rectf(glm::vec2(drag_box_left_, 0),
                                glm::vec2(drag_box_right_, drag_box_height_)));
}

void Slider::BeginDragging(glm::vec2& mouse_position) {
  double mouse_x = mouse_position.x;
  double mouse_y = mouse_position.y;
  is_dragged_ = (mouse_x >= drag_box_left_ && mouse_x <= drag_box_right_ &&
                 mouse_y >= 0 && mouse_y <= drag_box_height_);
}

void Slider::StopDragging(glm::vec2& mouse_position) {
  is_dragged_ = false;
}

}  // namespace epidemic_simulator