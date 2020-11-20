#include "calc.h"
#include <stdexcept>
#include <algorithm>
#include <stack>
#include <exception>

Calculator::Calculator(const std::string& expression) {
  StringToTokens(expression);
  PolishNotation();
  Process();
}

int Calculator::Calculate(const std::string& expression) {
  Calculator calculator_object(expression);
  if (calculator_object.stack_machine_.size() == 1) {
    return calculator_object.stack_machine_.top().value;
  } else {
    return 0;
  }
}

void Calculator::Process() {
  for (auto& token : postfix_notation_) {
    switch (token.type) {
      case (Calculator::Token::TokenType::constant): {
        stack_machine_.push(token);
        break;
      }
      case (Calculator::Token::TokenType::abs): {
        int curr_value = stack_machine_.top().value;
        stack_machine_.pop();
        stack_machine_.push(Calculator::Token(abs(curr_value)));
        break;
      }
      case (Calculator::Token::TokenType::unary_minus): {
        int curr_value = stack_machine_.top().value;
        stack_machine_.pop();
        stack_machine_.push(Calculator::Token(-curr_value));
        break;
      }
      case (Calculator::Token::TokenType::plus): {
        int value_1 = stack_machine_.top().value;
        stack_machine_.pop();
        int value_2 = stack_machine_.top().value;
        stack_machine_.pop();
        stack_machine_.push(Calculator::Token(value_2 + value_1));
        break;
      }
      case (Calculator::Token::TokenType::minus): {
        int value_1 = stack_machine_.top().value;
        stack_machine_.pop();
        int value_2 = stack_machine_.top().value;
        stack_machine_.pop();
        stack_machine_.push(Calculator::Token(value_2 - value_1));
        break;
      }
      case (Calculator::Token::TokenType::product): {
        int value_1 = stack_machine_.top().value;
        stack_machine_.pop();
        int value_2 = stack_machine_.top().value;
        stack_machine_.pop();
        stack_machine_.push(Calculator::Token(value_2 * value_1));
        break;
      }
      case (Calculator::Token::TokenType::division) : {
        int value_1 = stack_machine_.top().value;
        stack_machine_.pop();
        if (value_1 == 0) {
          throw std::runtime_error("Division by zero");
        }
        int value_2 = stack_machine_.top().value;
        stack_machine_.pop();
        stack_machine_.push(Calculator::Token(value_2 / value_1));
        break;
      }
      case (Calculator::Token::TokenType::module) : {
        int value_1 = stack_machine_.top().value;
        stack_machine_.pop();
        if (value_1 == 0) {
          throw std::runtime_error("Division by zero");
        }
        int value_2 = stack_machine_.top().value;
        stack_machine_.pop();
        stack_machine_.push(Calculator::Token(value_2 % value_1));
        break;
      }
      default:break;
    }
  }
}

Calculator::Token::Token(int new_value) {
  type = TokenType::constant;
  value = new_value;
}

Calculator::Token::Token(const std::string& input) {
  if (input == "abs") {
    type = TokenType::abs;
  } else {
    type = TokenType::constant;
    value = stoi(input);
  }
}

Calculator::Token::Token(char input) {
  switch (input) {
    case ('+'): {
      type = TokenType::plus;
      break;
    }
    case ('-'): {
      type = TokenType::minus;
      break;
    }
    case ('*'): {
      type = TokenType::product;
      break;
    }
    case ('/'): {
      type = TokenType::division;
      break;
    }
    case ('%'): {
      type = TokenType::module;
      break;
    }
    case ('('): {
      type = TokenType::left;
      break;
    }
    case (')'): {
      type = TokenType::right;
      break;
    }
    default: {
      type = TokenType::unknown;
      break;
    }
  }
}

bool IsDigit(char sign) {
  return sign >= '0' && sign <= '9';
}

bool Calculator::IsItUnaryMinus() {
  long long num_of_constants = std::count_if(infix_notation_.begin(),
                                             infix_notation_.end(),
            [](const Calculator::Token& token) {
              return token.type == Calculator::Token::TokenType::constant;
            });
  long long num_of_bin_operations = std::count_if(infix_notation_.begin(),
                                                  infix_notation_.end(),
            [](const Calculator::Token& token) {
              return token.type >= Calculator::Token::TokenType::plus &&
                     token.type <= Calculator::Token::TokenType::module;
            });
  return num_of_bin_operations == num_of_constants;
}

// transform string to the vector of tokens,
// considering each char
void Calculator::StringToTokens(const std::string& input) {
  long long i{0};
  while (i < input.length()) {
    if (input.at(i) == ' ') {
      ++i;
      continue;
    } else if (input.at(i) != '-' && input.at(i) != 'a'
        && Calculator::Token(input.at(i)).type
            != Calculator::Token::TokenType::unknown) {
      infix_notation_.emplace_back(input.at(i));
      ++i;
    } else if (input.at(i) == 'a') {
      infix_notation_.emplace_back("abs");
      i += 3;
    } else if (input.at(i) == '-') {
      if (infix_notation_.empty() || IsItUnaryMinus()) {
        Calculator::Token unary_minus;
        unary_minus.type = Calculator::Token::TokenType::unary_minus;
        infix_notation_.push_back(unary_minus);
        ++i;
      } else {
        infix_notation_.emplace_back(input.at(i));
        ++i;
      }
    } else if (IsDigit(input.at(i))) {
      std::string potential_number;
      potential_number += input.at(i);
      while (i < input.length() - 1 && IsDigit(input.at(i + 1))) {
        potential_number += input.at(i + 1);
        ++i;
      }
      infix_notation_.emplace_back(potential_number);
      ++i;
    }
  }
}

// transform to reverse polish notation
void Calculator::PolishNotation() {
  std::stack<Calculator::Token> stack;
  for (auto& token : infix_notation_) {
    switch (token.type) {
      case (Calculator::Token::TokenType::constant): {
        postfix_notation_.push_back(token);
        break;
      }
      case (Calculator::Token::TokenType::left): {
        stack.push(token);
        break;
      }
      case (Calculator::Token::TokenType::right): {
        while (stack.top().type != Calculator::Token::TokenType::left) {
          postfix_notation_.push_back(stack.top());
          stack.pop();
        }
        stack.pop();
        break;
      }
      case (Calculator::Token::TokenType::unary_minus):
      case (Calculator::Token::TokenType::abs): {
        stack.push(token);
        break;
      }
      case (Calculator::Token::TokenType::plus):
      case (Calculator::Token::TokenType::minus): {
        while (!stack.empty() &&
            stack.top().type >= Calculator::Token::TokenType::plus) {
          postfix_notation_.push_back(stack.top());
          stack.pop();
        }
        stack.push(token);
        break;
      }
      case (Calculator::Token::TokenType::product):
      case (Calculator::Token::TokenType::division):
      case (Calculator::Token::TokenType::module): {
        while (!stack.empty()
            && (stack.top().type >= Calculator::Token::TokenType::product)) {
          postfix_notation_.push_back(stack.top());
          stack.pop();
        }
        stack.push(token);
        break;
      }
      default:break;
    }
  }
  while (!stack.empty()) {
    postfix_notation_.push_back(stack.top());
    stack.pop();
  }
}

// FRIEND-CLASS FUNCTIONS

std::string TestingTool::GetPolishNotation() {
  Calculator calculator_object(current_expression_);
  return VectorOfTokensToString(calculator_object.postfix_notation_);
}

std::string TestingTool::GetTokenVector() {
  Calculator calculator_object(current_expression_);
  return VectorOfTokensToString(calculator_object.infix_notation_);
}

std::string TestingTool::TokenToString(const Calculator::Token& token) {
    switch (token.type) {
      case (Calculator::Token::TokenType::constant): {
        return std::to_string(token.value);
      }
      case Calculator::Token::TokenType::plus:
        return "+";
      case Calculator::Token::TokenType::minus:
        return "-";
      case Calculator::Token::TokenType::product:
        return "*";
      case Calculator::Token::TokenType::division:
        return "/";
      case Calculator::Token::TokenType::module:
        return "%";
      case Calculator::Token::TokenType::abs:
        return "abs";
      case Calculator::Token::TokenType::left:
        return "(";
      case Calculator::Token::TokenType::right:
        return ")";
      case Calculator::Token::TokenType::unary_minus:
        return "-";
      default:
        return " ";
    }
  }

std::string
TestingTool::VectorOfTokensToString(
    const std::vector<Calculator::Token>& tokens) {
  std::string result;
  for (auto& token : tokens) {
    result += (TokenToString(token) + " ");
  }
  return result;
}
