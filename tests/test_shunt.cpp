#include "shunt.hpp"

#include <catch2/catch_test_macros.hpp>
#include <cstddef>
#include <cstdint>

TEST_CASE("Basic shunting yard parser", "[parse]") {
  REQUIRE(shunt::parse("3+3+5") == "3 3 + 5 +");
  REQUIRE(shunt::parse("3+3*5") == "3 3 5 * +");
  REQUIRE(shunt::parse("3+3*5/10") == "3 3 5 * 10 / +");
}

TEST_CASE("Shunting-yard works with parens", "[parse]") {
  REQUIRE(shunt::parse("(3+3)*5/10") == "3 3 + 5 * 10 /");
  REQUIRE(shunt::parse("3+(3*5)/10") == "3 3 5 * 10 / +");
}

// Copilot-generated test cases
TEST_CASE("Basic parsing", "[parse]") {
  REQUIRE(shunt::parse("1+2") == "1 2 +");
  REQUIRE(shunt::parse("3-4") == "3 4 -");
  REQUIRE(shunt::parse("5*6") == "5 6 *");
  REQUIRE(shunt::parse("7/8") == "7 8 /");
}

TEST_CASE("Edge cases", "[shunting-yard]") {
  REQUIRE(shunt::parse("1") == "1");
  REQUIRE(shunt::parse("1+2") == "1 2 +");
  REQUIRE(shunt::parse("(((((1+2)))))") == "1 2 +");
  REQUIRE(shunt::parse("3+(4*5)-6") == "3 4 5 * + 6 -");
}

TEST_CASE("Operator precedence", "[shunting-yard]") {
  REQUIRE(shunt::parse("1+2*3") == "1 2 3 * +");
  REQUIRE(shunt::parse("4*5+6") == "4 5 * 6 +");
  REQUIRE(shunt::parse("7+8/2") == "7 8 2 / +");
}

// TEST_CASE("Multiple operators", "[shunting-yard]") {
//   REQUIRE(shunt::parse("1+2+3") == "12+3+");
//   REQUIRE(shunt::parse("8-5+2") == "85-2+");
//   REQUIRE(shunt::parse("2*3*4") == "23*4*");
//   REQUIRE(shunt::parse("9/3/1") == "93/1/");
// }

// TEST_CASE("Parentheses", "[shunting-yard]") {
//   REQUIRE(shunt::parse("(1+2)*3") == "12+3*");
//   REQUIRE(shunt::parse("4*(5+6)") == "456+*");
//   REQUIRE(shunt::parse("7*(8/2)") == "782/*");
//   REQUIRE(shunt::parse("(1+2)*(3+4)") == "12+34+*");
// }

// TEST_CASE("Nested parentheses", "[shunting-yard]") {
//   REQUIRE(shunt::parse("((1+2)*3)-4") == "12+3*4-");
//   REQUIRE(shunt::parse("5+(6*(7+8))") == "5678+*+");
//   REQUIRE(shunt::parse("((1+2)+(3+4))*5") == "12+34++5*");
// }

// TEST_CASE("Complex expressions", "[shunting-yard]") {
//   REQUIRE(shunt::parse("1+2*3-4/5") == "123*45/-+");
//   REQUIRE(shunt::parse("1+2*3/4-5") == "123*4/+5-");
//   REQUIRE(shunt::parse("9-(3+4)*2") == "934+2*-");
// }
