#ifndef SHUNT_HPP
#define SHUNT_HPP

#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// Does operator o1 have equal to or higher precedence than o2
namespace {
inline int precedence(char o) {
  if (o == '+' or o == '-') {
    return 4;
  } else if (o == '*' or o == '/') {
    return 3;
  } else {
    return 1'000'000;
  }
}
} // namespace

namespace shunt {
inline std::string parse(std::string expr) {
  // Parse expressions of integers e.g. 1 + 2 * 5 / 2
  // TODO: allow for functions
  // TODO: allow for decimal points
  // TODO: check for bad characters
  // TODO: allow for evaluating variables from the heap
  int n = expr.length();
  std::string out;
  std::vector<char> op_stack;

  auto it = expr.begin();
  char s_prev = ' ';
  while (it != expr.end()) {
    // Get the current character
    char s = *it;

    // If it's a number, just push onto the output
    if ((s >= '0' && s <= '9')) {
      out += s;
    } else {
      if (s_prev >= '0' && s_prev <= '9') {
        // Add a space after a sequence of numbers
        out += ' ';
      }
      if (s == '(') {
        op_stack.push_back(s);
      } else if (s == ')') {
        if (op_stack.empty()) {
          throw std::runtime_error("Unbalanced parentheses");
        }

        // While the back is not a parens, add stuff to the operator queue
        char back = op_stack.back();
        while (back != '(') {
          out += back;
          out += ' ';

          op_stack.pop_back();
          back = op_stack.back();
        }

        // We *should* have an left parenthesis on the back
        if (back == '(') {
          op_stack.pop_back();
        } else {
          throw std::runtime_error("Unbalanced parentheses");
        }
      } else if (s == '+' or s == '-' or s == '*' or s == '/') {
        // If the stack is empty, just push it straight on
        if (op_stack.empty()) {
          op_stack.push_back(s);
        } else {
          // Get the last operator
          char o1 = s;
          char o2 = op_stack.back();

          while (precedence(o2) <= precedence(o1)) {
            // Add spaces around operators for clarity
            out += o2;
            out += ' ';

            op_stack.pop_back();
            if (op_stack.empty()) {
              break;
            } else {
              o2 = op_stack.back();
            }
          }
          op_stack.push_back(s);
        }
      }
    }

    // Set the previous iterate and increment
    s_prev = *it;
    ++it;
  }

  // Push the remaining operators from the queue
  while (!op_stack.empty()) {
    out += ' ';
    out += op_stack.back();
    op_stack.pop_back();
  }

  // Remove the last character if it is a space
  if (out.back() == ' ') {
    out.pop_back();
  }

  return out;
}
} // namespace shunt

#endif
