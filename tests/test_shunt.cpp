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

TEST_CASE("Function support in shunting yard", "[parse][functions]") {
  REQUIRE(shunt::parse("sin(0)") == "0 sin");
  REQUIRE(shunt::parse("cos(1)") == "1 cos");
  REQUIRE(shunt::parse("exp(2)") == "2 exp");
  REQUIRE(shunt::parse("sin(1+2)") == "1 2 + sin");
  REQUIRE(shunt::parse("cos(1)*2") == "1 cos 2 *");
  REQUIRE(shunt::parse("sin(1)+cos(2)") == "1sin2cos+");
  REQUIRE(shunt::parse("exp(1+sin(2))") == "12sin+exp");
  REQUIRE(shunt::parse("sin(cos(0))") == "0cossin");
  REQUIRE(shunt::parse("sin(1+2)*3") == "12+sin3*");
  REQUIRE(shunt::parse("sin(1+2*3)") == "123*+sin");
}

TEST_CASE("Multiple operators", "[shunting-yard]") {
  REQUIRE(shunt::parse("1+2+3") == "1 2 + 3 +");
  REQUIRE(shunt::parse("8-5+2") == "8 5 - 2 +");
  REQUIRE(shunt::parse("2*3*4") == "2 3 * 4 *");
  REQUIRE(shunt::parse("9/3/1") == "9 3 / 1 /");
}

TEST_CASE("Nested parentheses", "[shunting-yard]") {
  REQUIRE(shunt::parse("((1+2)*3)-4") == "1 2 + 3 * 4 -");
  REQUIRE(shunt::parse("5+(6*(7+8))") == "5 6 7 8 + * +");
  REQUIRE(shunt::parse("((1+2)+(3+4))*5") == "1 2 + 3 4 + + 5 *");
}

TEST_CASE("Parentheses", "[shunting-yard]") {
  REQUIRE(shunt::parse("(1+2)*3") == "1 2 + 3 *");
  REQUIRE(shunt::parse("4*(5+6)") == "4 5 6 + *");
  REQUIRE(shunt::parse("7*(8/2)") == "7 8 2 / *");
  REQUIRE(shunt::parse("(1+2)*(3+4)") == "1 2 + 3 4 + *");
}

TEST_CASE("Complex expressions", "[shunting-yard]") {
  REQUIRE(shunt::parse("1+2*3-4/5") == "1 2 3 * 4 5 / - +");
  REQUIRE(shunt::parse("1+2*3/4-5") == "1 2 3 * 4 / + 5 -");
  REQUIRE(shunt::parse("9-(3+4)*2") == "9 3 4 + 2 * - ");
}
