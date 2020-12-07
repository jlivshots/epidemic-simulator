#include <core/button.h>

#include <catch2/catch.hpp>

TEST_CASE("Button with dimensions 10 X 15") {
  SECTION("Playing status is false by default") {

  }

  SECTION("Clicking outside of the button does not change playing status") {

  }

  SECTION("Clicking outside of the button for ClickMouse() returns false") {

  }

  SECTION("Clicking inside the button inverts playing status from false to true") {

  }

  SECTION("Clicking inside the button inverts playing status from true to false") {

  }

  SECTION("Clicking inside the button for ClickMouse() returns true") {

  }
  SECTION("Clicking on the button edge inverts playing status") {

  }

  SECTION("Clicking on the button edge for ClickMouse() returns true") {

  }
}