#include <gtest/gtest.h>
#include "date.h"

TEST(Date, Sample) {
  Date date(1, 2, 3333);
  ASSERT_EQ(date.day, 1);
  ASSERT_EQ(date.month, 2);
  ASSERT_EQ(date.year, 3333);
  ASSERT_EQ(DateToString(date), "01.02.3333");
}

TEST(Date, ChekHelpFunc) {
  {
    Date date_1(23, 12, 3947);
    Date date_2(1, 1, 8999);

    EXPECT_TRUE(PreviousDate(date_1) ==Date(22, 12, 3947));
    EXPECT_TRUE(PreviousDate(date_2) == Date(31, 12, 8998));
    EXPECT_TRUE(NextDate(date_1) == Date(24, 12, 3947));
    EXPECT_TRUE(NextDate(date_2) == Date(2, 1, 8999));

    EXPECT_EQ(JDN_system(date_2) - JDN_system(date_1), 1844850);
    EXPECT_TRUE(IsLeap(date_1) == false);
    EXPECT_TRUE(IsLeap(date_2) == false);

    EXPECT_EQ(NumberOfDaysInMonth(date_1), 31);
    EXPECT_EQ(NumberOfDaysInMonth(date_2), 31);
  }
  {
    Date date_1(28, 2, 300);
    Date date_2(28, 2, 400);

    EXPECT_TRUE(PreviousDate(date_1) == Date(27, 2, 300));
    EXPECT_TRUE(PreviousDate(date_2) == Date(27, 2, 400));
    EXPECT_TRUE(NextDate(date_1) == Date(1, 3, 300));
    EXPECT_TRUE(NextDate(date_2) == Date(29, 2, 400));

    EXPECT_EQ(JDN_system(date_2) - JDN_system(date_1), 36524);
    EXPECT_TRUE(IsLeap(date_1) == false);
    EXPECT_TRUE(IsLeap(date_2) == true);

    EXPECT_EQ(NumberOfDaysInMonth(date_1), 28);
    EXPECT_EQ(NumberOfDaysInMonth(date_2), 29);
  }
}