#ifndef SHUNT_HPP
#define SHUNT_HPP

#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace shunt {
// Does operator o1 have equal to or higher precedence than o2
inline int precedence(char o) {
  if (o == '+' or o == '-') {
    return 4;
  } else if (o == '*' or o == '/') {
    return 3;
  } else {
    return 1'000'000;
  }
}

inline void eval(std::string expr) {
  // Parse expressions of integers e.g. 1 + 2 * 5 / 2
  // TODO: check for bad characters
  // TODO: allow for parens
  // TODO: allow for decimal points
  // TODO: allow for functions
  // TODO: allow for evaluating variables from the heap
  int n = expr.length();
  std::string out;
  std::vector<char> op_stack;

  for (int i = 0; i < n; ++i) {
    char s = expr.at(i);

    // If it's a number, just push onto the output
    if (s >= '0' && s <= '9') {
      out += s;
    } else if (s == '+' or s == '-' or s == '*' or s == '/') {
      // If the stack is empty, just push it straight on
      if (op_stack.empty()) {
        op_stack.push_back(s);
      } else {
        // Get the last operator
        char o1 = s;
        char o2 = op_stack.back();

        while (precedence(o2) <= precedence(o1) and !op_stack.empty()) {
          out += o2;
          op_stack.pop_back();
          o2 = op_stack.back();
        }
        op_stack.push_back(s);
      }
    }
  }

  // Push the remaining operators from the queue
  while (!op_stack.empty()) {
    out += op_stack.back();
    op_stack.pop_back();
  }
  std::cout << out << std::endl;
}
} // namespace shunt

#endif
