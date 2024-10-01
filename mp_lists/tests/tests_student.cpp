#include <catch2/catch_test_macros.hpp>
#include "tests_helper.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include "List.h"

using namespace cs225;

// You may write your own test cases in this file to test your code.
// Test cases in this file are not graded.

TEST_CASE("My Test Case", "") {
    bool student_wrote_test_case = false;

    REQUIRE( student_wrote_test_case );
}
TEST_CASE("My Test Case: reverse", "[weight=5][part=2]") {
  PNG in;        in.readFromFile("../data/alma.png");
  PNG expected;  expected.readFromFile("../data/expected-reverse.png");

  List<HSLAPixel> list = imageToList(in);
  list.reverse();
  PNG out = listToImage(list, in.width(), in.height());
  out.writeToFile("actual-reverse.png");
  INFO("Output image `out` saved as actual-reverse.png");
}