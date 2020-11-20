#include <vector>
#include <string>
#include <stack>

#ifndef CALC_H_
#define CALC_H_

class Calculator {
 public:
  static int Calculate(const std::string& expression);
  friend class TestingTool;

 private:
  explicit Calculator(const std::string&);
  struct Token {
    Token() = default;
    explicit Token(const std::string&);
    explicit Token(int);
    explicit Token(char i);
    enum TokenType {
      left,
      right,
      constant,
      plus,
      minus,
      product,
      division,
      module,
      abs,
      unary_minus,
      unknown
    };
    TokenType type = TokenType::unknown;
    int value = 0;
  };

  std::vector<Token> infix_notation_;
  std::vector<Token> postfix_notation_;
  std::stack<Token> stack_machine_;

  void PolishNotation();
  void StringToTokens(const std::string&);
  bool IsItUnaryMinus();
  void Process();
};

class TestingTool {
 public:
  explicit TestingTool(const std::string& expression) {
    current_expression_ = expression;
  }
  std::string GetPolishNotation();
  std::string GetTokenVector();

 private:
  static std::string TokenToString(const Calculator::Token&);
  static std::string
  VectorOfTokensToString(const std::vector<Calculator::Token>&);
  std::string current_expression_;
};

bool IsDigit(char);

#endif  // CALC_H_
