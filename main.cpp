#include <string>

#include "src/shunt.hpp"

int main() {
  shunt::eval("3+3+5");  // 33+5+
  shunt::eval("3+3*5");  // 335*+
  shunt::eval("3+3*5/10");  // 335*10/+
  return 0;
}
