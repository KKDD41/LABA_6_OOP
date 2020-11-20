#include <gtest/gtest.h>
#include "calc.h"

TEST(Calculator, Sample) {
  ASSERT_EQ(Calculator::Calculate("2 + abs(2 * 2)"), 6);
}

TEST(Test_1, UnaryVSBinaryMinus) {
  EXPECT_EQ(Calculator::Calculate("-5 + 10 - 7"), -2);
  EXPECT_EQ(Calculator::Calculate("-5 + 10-7"), -2);
  EXPECT_EQ(Calculator::Calculate("4*-9 % 7"), -1);
  EXPECT_EQ(Calculator::Calculate("4 * - 9 % 7"), -1);
}

TEST(Test_2, Priority) {
  EXPECT_EQ(Calculator::Calculate("3 * 8 / 5 % 3"), 1);
  EXPECT_EQ(Calculator::Calculate("3 / 5 * 8 % 3"), 0);
  EXPECT_EQ(Calculator::Calculate("3 % 2 / -1 * 5"), -5);
  EXPECT_EQ(Calculator::Calculate("333*111/111%110"), 3);
  EXPECT_EQ(Calculator::Calculate("-0"), 0);
}

TEST(Test_3, UnaryOperations) {
  EXPECT_EQ(Calculator::Calculate("abs(-2*-9/-9)"), 2);
  EXPECT_EQ(Calculator::Calculate("-abs(-8+-1)"), -9);
  EXPECT_EQ(Calculator::Calculate("0-3 +-abs(7 -8)"), -4);
  EXPECT_EQ(Calculator::Calculate("0-3 -abs(7 -8)"), -4);
  EXPECT_EQ(Calculator::Calculate("-abs(-abs(9 - abs(-3 - abs(9))))"),
            -3);
  EXPECT_EQ(Calculator::Calculate("0-6 /-abs(2)"), 3);
}

TEST(Test_4, SomethingCheck) {
  EXPECT_EQ(Calculator::Calculate("2 + abs(2 * 2)"), 6);
  EXPECT_EQ(Calculator::Calculate("2 + 2"), 4);
  EXPECT_EQ(Calculator::Calculate("-2 + 2"), 0);
  EXPECT_EQ(Calculator::Calculate("15 / 3 + (18 % 3 + 15 * 1)"), 20);
  EXPECT_EQ(Calculator::Calculate("15 / 3 + (18 % 3 + (-15) * 1)"), -10);
  EXPECT_EQ(Calculator::Calculate("15 / 3 + (18 % 3 + abs(-(16 - 23 % 5) - 1))"),
            19);
  EXPECT_EQ(Calculator::Calculate("15 / 3 + abs(18 % 3 + (-15) * 1)"), 20);
}

TEST(Test_5, WhereAreTwoPoints) {
  EXPECT_EQ(Calculator::Calculate("-029837"), -29837);
  EXPECT_EQ(Calculator::Calculate("3835 * 23% 31 -abs(918 - 3)"),
            3835 * 23 % 31 - abs(918 - 3));
  EXPECT_EQ(Calculator::Calculate(
      "-abs(-6 -3) - 12523 % abs(12314) - 9 + abs(-8381*6)/99"),
            -abs(-6 - 3) - 12523 % abs(12314) - 9 + abs(-8381 * 6) / 99);
  EXPECT_EQ(Calculator::Calculate("abs abs( - abs(-abs(937 - 3 * 1% 22)-5% 8))"),
            abs(abs(-abs(-abs(937 - 3 * 1 % 22) - 5 % 8))));
}

TEST(Test_5, ExeptionCheck) {
  EXPECT_THROW(Calculator::Calculate("1234 / 0"),
               std::runtime_error);
  EXPECT_THROW(Calculator::Calculate("8273 % 0"),
               std::runtime_error);
}

TEST(Test_6, ConvertingFunctionsTesting) {
  {
    TestingTool expression_1{"-3 + 5 * 72"};
    EXPECT_EQ(expression_1.GetTokenVector(), "- 3 + 5 * 72 ");
    EXPECT_EQ(expression_1.GetPolishNotation(), "3 - 5 72 * + ");
  }
  {
    TestingTool expression_1{"abs(-3) + 5 * 72 % (3 - 0)"};
    EXPECT_EQ(expression_1.GetTokenVector(),
              "abs ( - 3 ) + 5 * 72 % ( 3 - 0 ) ");
    EXPECT_EQ(expression_1.GetPolishNotation(),
              "3 - abs 5 72 * 3 0 - % + ");
  }
}