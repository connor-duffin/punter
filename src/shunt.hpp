#ifndef SHUNT_HPP
#define SHUNT_HPP

#include <cctype>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <vector>

/**
 * A constant of the known functions in this repo - use inline variable so it
 * this variable is not copied across different files.
 */
inline const std::unordered_set<std::string> KNOWN_FUNCTIONS{
  "sin", "cos", "tan", "asin", "acos", "atan", "cosh", "sinh", "tanh", "acosh",
  "asinh", "atanh", "exp", "log", "ceil", "floor", "round"
};

namespace shunt {
/**
 * @brief Fetch the precedence of the operator, defined from here:
 * https://en.wikipedia.org/wiki/Order_of_operations#Programming_languages
 * @param o The string containing the operator to be parsed.
 * @return The value of the operator precedence.
 */
inline int precedence(const std::string &o) {
  if (o == "+" or o == "-") {
    return 4;
  } else if (o == "*" or o == "/") {
    return 3;
  } else {
    return 1'000'000;
  }
}

/**
 * @brief Helper function to check if the provided string is a function.
 * @param f A function.
 * @return True if a function, false otherwise.
 */
inline bool is_fun(const std::string &f) {
  if (KNOWN_FUNCTIONS.count(f)) {
    return true;
  } else {
    return false;
  }
}

/**
 * @brief Parse basic mathematical expressions of integers into
 * postfix/reverse-Polish notation.
 *
 * Currently supports only integers, (* / + -), and some basic functions.
 *
 * @param expr A mathematical expression.
 * @return A string giving the RPN representation of the expression.
 */
inline std::string parse(const std::string &expr) {
  std::vector<std::string> op_stack;
  std::vector<std::string> out;

  auto it = expr.begin();
  char s_prev = ' ';
  while (it != expr.end()) {
    char s = *it;

    // Get the current character
    // If it's a number, just push onto the output
    if (std::isdigit(s)) {
      std::string num;
      while (std::isdigit(s)) {
        num += s;
        s_prev = s;

        ++it;
	if (it == expr.end()) break;
	s = *it;
      }
      out.push_back(num);
    } else {
      // If alphabet character then it is a function
      if (std::isalpha(s)) {
        // Build the function operator
        std::string fun;
        while (std::isalpha(s)) {
          fun += s;
          s_prev = s;

          ++it;
	  if (it == expr.end()) break;
	  s = *it;
        }

	if (is_fun(fun)) {
          op_stack.push_back(fun);
        } else {
	  throw std::runtime_error("Provided function not recognised");
	}
      } else if (s == '(') {
        // Cast to a string and go next
        op_stack.push_back(std::string(1, s));

        // Increment the pointer
        s_prev = s;
        ++it;
      } else if (s == ')') {
        if (op_stack.empty()) {
          throw std::runtime_error("Unbalanced parentheses");
        }

        // While the back is not a parens, add stuff to the operator queue
        std::string back = op_stack.back();
        while (back != "(") {
          out.push_back(back);
          op_stack.pop_back();
          back = op_stack.back();
        }

        // We *should* have a left parenthesis on the back
        if (back == "(") {
          op_stack.pop_back();
        } else {
          throw std::runtime_error("Unbalanced parentheses");
        }

	// Finally if there is a function left over, pop it
	back = op_stack.back();
        if (is_fun(back)) {
          out.push_back(back);
          op_stack.pop_back();
	}

        // Increment the pointer
        s_prev = s;
        ++it;
      } else if (s == '+' or s == '-' or s == '*' or s == '/') {

        // If the stack is empty, just push it straight on
        if (op_stack.empty()) {
          op_stack.push_back(std::string(1, s));
        } else {
          // Get the last operator
          std::string o1(1, s);
          std::string o2 = op_stack.back();

          while (precedence(o2) <= precedence(o1)) {
            // Add spaces around operators for clarity
            out.push_back(o2);

            op_stack.pop_back();
            if (op_stack.empty()) {
              break;
            } else {
              o2 = op_stack.back();
            }
          }
          op_stack.push_back(std::string(1, s));
        }

        // Increment the pointer
        s_prev = s;
        ++it;
      }
    }
  }

  // Push the remaining operators from the queue
  while (!op_stack.empty()) {
    out.push_back(op_stack.back());
    op_stack.pop_back();
  }

  // Concatenate the results into a string, with spaces around each
  std::string out_string{};
  for (auto it = out.begin(); it != out.end(); ++it) {
    out_string += *it;
    if ((it + 1) != out.end()) {
      out_string += " ";
    }
  }
  return out_string;
}
} // namespace shunt

#endif
