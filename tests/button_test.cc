#include <core/button.h>

#include <catch2/catch.hpp>

TEST_CASE("Button with dimensions 10 X 15") {
  epidemic_simulator::Button button(glm::vec2(10, 15));
  SECTION("Playing status is false by default") {
    REQUIRE_FALSE(button.IsPlaying());
  }

  SECTION("Clicking outside of the button does not change playing status") {
    button.ClickMouse(glm::vec2(654, 465));
    REQUIRE_FALSE(button.IsPlaying());
  }

  SECTION("Clicking outside of the button for ClickMouse() returns false") {
    REQUIRE_FALSE(button.ClickMouse(glm::vec2(654, 465)));
  }

  SECTION(
      "Clicking inside the button inverts playing status from false to true") {
    button.SetPlayingStatus(false);
    button.ClickMouse(glm::vec2(2, 3));
    REQUIRE(button.IsPlaying());
  }

  SECTION(
      "Clicking inside the button inverts playing status from true to false") {
    button.SetPlayingStatus(true);
    button.ClickMouse(glm::vec2(2, 3));
    REQUIRE_FALSE(button.IsPlaying());
  }

  SECTION("Clicking inside the button for ClickMouse() returns true") {
    REQUIRE(button.ClickMouse(glm::vec2(2, 3)));
  }

  SECTION("Clicking on the button edge inverts playing status from true to false") {
    button.SetPlayingStatus(true);
    button.ClickMouse(glm::vec2(8, 15));
    REQUIRE_FALSE(button.IsPlaying());
  }

  SECTION("Clicking on the button edge inverts playing status from false to true") {
    button.SetPlayingStatus(false);
    button.ClickMouse(glm::vec2(0, 15));
    REQUIRE(button.IsPlaying());
  }

  SECTION("Clicking on the button edge for ClickMouse() returns true") {
    REQUIRE(button.ClickMouse(glm::vec2(8, 15)));
  }
}

TEST_CASE("Button with dimensions 5 X 10") {
  epidemic_simulator::Button button(glm::vec2(5, 10));
  SECTION("Playing status is false by default") {
    REQUIRE_FALSE(button.IsPlaying());
  }

  SECTION("Clicking outside of the button does not change playing status") {
    button.ClickMouse(glm::vec2(654, 465));
    REQUIRE_FALSE(button.IsPlaying());
  }

  SECTION("Clicking outside of the button for ClickMouse() returns false") {
    REQUIRE_FALSE(button.ClickMouse(glm::vec2(654, 465)));
  }

  SECTION(
      "Clicking inside the button inverts playing status from false to true") {
    button.SetPlayingStatus(false);
    button.ClickMouse(glm::vec2(2, 3));
    REQUIRE(button.IsPlaying());
  }

  SECTION(
      "Clicking inside the button inverts playing status from true to false") {
    button.SetPlayingStatus(true);
    button.ClickMouse(glm::vec2(2, 3));
    REQUIRE_FALSE(button.IsPlaying());
  }

  SECTION("Clicking inside the button for ClickMouse() returns true") {
    REQUIRE(button.ClickMouse(glm::vec2(2, 3)));
  }

  SECTION("Clicking on the button edge inverts playing status from true to false") {
    button.SetPlayingStatus(true);
    button.ClickMouse(glm::vec2(2, 10));
    REQUIRE_FALSE(button.IsPlaying());
  }

  SECTION("Clicking on the button edge inverts playing status from false to true") {
    button.SetPlayingStatus(false);
    button.ClickMouse(glm::vec2(1, 10));
    REQUIRE(button.IsPlaying());
  }

  SECTION("Clicking on the button edge for ClickMouse() returns true") {
    REQUIRE(button.ClickMouse(glm::vec2(0, 2)));
  }
}