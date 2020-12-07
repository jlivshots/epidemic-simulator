#include <core/slider.h>

#include <catch2/catch.hpp>

TEST_CASE(
    "Drag box location generates correctly for slider width 100 and drag width "
    "10") {
  epidemic_simulator::Slider slider(0, 1, 10, glm::vec2(100, 20));
  SECTION("BeginDragging() with mouse location within drag box sets is_dragged_ to true") {
    slider.BeginDragging(glm::vec2(1,1));
    REQUIRE(slider.IsDragged());
  }

  SECTION("BeginDragging() with mouse location on border of drag box sets is_dragged_ to true") {
    slider.BeginDragging(glm::vec2(0,0));
    REQUIRE(slider.IsDragged());
  }

  SECTION("BeginDragging() with mouse location outside drag box sets is_dragged_ to false") {
    slider.BeginDragging(glm::vec2(30,0));
    REQUIRE_FALSE(slider.IsDragged());
  }

  SECTION("Slider is not dragged at initialization") {
    REQUIRE_FALSE(slider.IsDragged());
  }

  SECTION("StopDragging() sets is_dragged_ to false") {
    slider.BeginDragging(glm::vec2(1,1));
    REQUIRE(slider.IsDragged());
    slider.StopDragging();
    REQUIRE_FALSE(slider.IsDragged());
  }

  SECTION("Drag box generates correctly initially") {
    ci::Rectf drag_box = slider.GenerateDragBox();
    REQUIRE(drag_box.getUpperLeft().x == 0);
    REQUIRE(drag_box.getUpperLeft().y == 0);
    REQUIRE(drag_box.getLowerRight().x == 10);
    REQUIRE(drag_box.getLowerRight().y == 20);
  }

  SECTION(
      "UpdateSlider() call doesn't move drag box when slider isn't being "
      "dragged") {
    slider.UpdateSlider(glm::vec2(50,50));
    ci::Rectf drag_box = slider.GenerateDragBox();
    REQUIRE(drag_box.getUpperLeft().x == 0);
    REQUIRE(drag_box.getUpperLeft().y == 0);
    REQUIRE(drag_box.getLowerRight().x == 10);
    REQUIRE(drag_box.getLowerRight().y == 20);
  }

  SECTION(
      "UpdateSlider() call moves to correct location when slider is being "
      "dragged and mouse is within slider") {
    slider.BeginDragging(glm::vec2(2,2));
    slider.UpdateSlider(glm::vec2(50,10));
    ci::Rectf drag_box = slider.GenerateDragBox();
    REQUIRE(drag_box.getUpperLeft().x == 45);
    REQUIRE(drag_box.getUpperLeft().y == 0);
    REQUIRE(drag_box.getLowerRight().x == 55);
    REQUIRE(drag_box.getLowerRight().y == 20);
  }

  SECTION(
      "UpdateSlider() call moves to correct location when slider is being "
      "dragged and mouse is to the left of the slider") {
    slider.BeginDragging(glm::vec2(2,2));
    slider.UpdateSlider(glm::vec2(50,50));
    slider.UpdateSlider(glm::vec2(-20, -10));
    ci::Rectf drag_box = slider.GenerateDragBox();
    REQUIRE(drag_box.getUpperLeft().x == 0);
    REQUIRE(drag_box.getUpperLeft().y == 0);
    REQUIRE(drag_box.getLowerRight().x == 10);
    REQUIRE(drag_box.getLowerRight().y == 20);
  }

  SECTION(
      "UpdateSlider() call moves to correct location when slider is being "
      "dragged and mouse is to the right of the slider") {
    slider.BeginDragging(glm::vec2(2,2));
    slider.UpdateSlider(glm::vec2(500,888));
    ci::Rectf drag_box = slider.GenerateDragBox();
    REQUIRE(drag_box.getUpperLeft().x == 90);
    REQUIRE(drag_box.getUpperLeft().y == 0);
    REQUIRE(drag_box.getLowerRight().x == 100);
    REQUIRE(drag_box.getLowerRight().y == 20);
  }

  SECTION(
      "UpdateSlider() call remains in place when slider is updated to the "
      "same location") {
    slider.BeginDragging(glm::vec2(2,2));
    slider.UpdateSlider(glm::vec2(500,888));
    slider.UpdateSlider(glm::vec2(500,888));
    ci::Rectf drag_box = slider.GenerateDragBox();
    REQUIRE(drag_box.getUpperLeft().x == 90);
    REQUIRE(drag_box.getUpperLeft().y == 0);
    REQUIRE(drag_box.getLowerRight().x == 100);
    REQUIRE(drag_box.getLowerRight().y == 20);
  }

  SECTION("UpdateSlider() call generates correct drag box when mouse is within drag box but moves") {
    slider.BeginDragging(glm::vec2(2,2));
    slider.UpdateSlider(glm::vec2(9,9));
    ci::Rectf drag_box = slider.GenerateDragBox();
    REQUIRE(drag_box.getUpperLeft().x == 4);
    REQUIRE(drag_box.getUpperLeft().y == 0);
    REQUIRE(drag_box.getLowerRight().x == 14);
    REQUIRE(drag_box.getLowerRight().y == 20);
  }
}

TEST_CASE(
    "Drag box location generates correctly for slider width 50 and drag width "
    "5") {
  SECTION("BeginDragging() with mouse location within drag box sets is_dragged_ to true") {
  }

  SECTION("BeginDragging() with mouse location on border of drag box sets is_dragged_ to true") {
  }

  SECTION("BeginDragging() with mouse location outside drag box sets is_dragged_ to false") {
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