#include "shunt.hpp"

#include <catch2/catch_test_macros.hpp>
#include <cstddef>
#include <cstdint>

TEST_CASE("Basic shunting yard parser", "[parse]") {
  REQUIRE(shunt::parse("3+3+5") == "33+5+");
  REQUIRE(shunt::parse("3+3*5") == "335*+");
  REQUIRE(shunt::parse("3+3*5/10") == "335*10/+");
}

TEST_CASE("Shunting-yard works with parens", "[parse]") {
  REQUIRE(shunt::parse("(3+3)*5/10") == "33+5*10/");
  REQUIRE(shunt::parse("3+(3*5)/10") == "335*10/+");
}
