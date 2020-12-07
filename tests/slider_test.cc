#include <core/slider.h>

#include <catch2/catch.hpp>

TEST_CASE(
    "Drag box location generates correctly for slider width 100 and drag width "
    "10") {
  SECTION("Mouse location within drag box sets is_dragged_ to true") {
  }

  SECTION("Mouse location on border of drag box sets is_dragged_ to true") {
  }

  SECTION("Mouse location outside drag box sets is_dragged_ to false") {
  }

  SECTION("StopDragging() sets is_dragged_ to false") {
  }

  SECTION("Drag box generates correctly initially") {
  }

  SECTION(
      "UpdateSlider() call doesn't move drag box when slider isn't being "
      "dragged") {
  }

  SECTION(
      "UpdateSlider() call moves to correct location when slider is being "
      "dragged and mouse is within slider") {
  }

  SECTION(
      "UpdateSlider() call moves to correct location when slider is being "
      "dragged and mouse is to the left of the slider") {
  }

  SECTION(
      "UpdateSlider() call moves to correct location when slider is being "
      "dragged and mouse is to the right of the slider") {
  }

  SECTION(
      "UpdateSlider() call remains in place when slider is updated to the "
      "same location") {
  }
}

TEST_CASE(
    "Drag box location generates correctly for slider width 50 and drag width "
    "5") {
  SECTION("Mouse location within drag box sets is_dragged_ to true") {
  }

  SECTION("Mouse location on border of drag box sets is_dragged_ to true") {
  }

  SECTION("Mouse location outside drag box sets is_dragged_ to false") {
  }

  SECTION("StopDragging() sets is_dragged_ to false") {
  }

  SECTION("Drag box generates correctly initially") {
  }

  SECTION(
      "UpdateSlider() call doesn't move drag box when slider isn't being "
      "dragged") {
  }

  SECTION(
      "UpdateSlider() call moves to correct location when slider is being "
      "dragged and mouse is within slider") {
  }

  SECTION(
      "UpdateSlider() call moves to correct location when slider is being "
      "dragged and mouse is to the left of the slider") {
  }

  SECTION(
      "UpdateSlider() call moves to correct location when slider is being "
      "dragged and mouse is to the right of the slider") {
  }

  SECTION(
      "UpdateSlider() call remains in place when slider is updated to the "
      "same location") {
  }
}

TEST_CASE(
    "Slider value updates correctly for slider length 100 and minimum value of "
    "5") {
  SECTION("Slider initial value is that of the minimum value") {
  }
  SECTION("Value updated correctly when slider is dragged") {
  }
  SECTION("Value remains unchanged when slider is not moved") {
  }
}

TEST_CASE(
    "Slider value updates correctly for slider length 50 and minimum value of "
    "2") {
  SECTION("Slider initial value is that of the minimum value") {
  }
  SECTION("Value updated correctly when slider is dragged") {
  }
  SECTION("Value remains unchanged when slider is not moved") {
  }
}