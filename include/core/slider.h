#ifndef EPIDEMIC_SIMULATOR_SLIDER_H
#define EPIDEMIC_SIMULATOR_SLIDER_H

#include "cinder/gl/gl.h"
namespace epidemic_simulator {
class Slider {
 public:
  /**
   * Instantiates a new Slider object. Assumes the top left corner of the slider
   * is (0,0).
   * @param min_value the minimum value of the slider. Defaults current_value_
   * to min_value.
   * @param max_value the maximum value of the slider.
   * @param drag_box_width the width of the box that can be dragged.
   * @param bottom_right_corner the bottom right corner of the slider.
   */
  Slider(double min_value, double max_value, float drag_box_width,
         glm::vec2& bottom_right_corner);

  /**
   * Returns the value of the slider and the rectangle of the drag box.
   * @param mouse_position the vec2 position of the mouse.
   * @return a pair consisting of the double value of the slider and the
   * rectangle drag box.
   */
  std::pair<double, ci::Rectf> UpdateSlider(glm::vec2& mouse_position);

  /**
   * If the mouse_position is inside the drag box, method sets is_dragged_ to
   * true. This method is intended to be called for each slider in the
   * MouseDown() method in epidemic_app.cc.
   * @param mouse_position the current position of the mouse.
   */
  void BeginDragging(glm::vec2& mouse_position);

  /**
   * Sets is_dragged_ to false. Method is intended to be called for each slider
   * in the MouseUp() method in epidemic_app.cc.
   * @param mouse_position
   */
  void StopDragging(glm::vec2& mouse_position);

 private:
  double drag_box_height_;
  float drag_box_width_;
  double drag_box_left_;
  double drag_box_right_;
  double sliding_width_;
  double current_value_;
  bool is_dragged_;

};
}  // namespace epidemic_simulator

#endif  // EPIDEMIC_SIMULATOR_SLIDER_H
