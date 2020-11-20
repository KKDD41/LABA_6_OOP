#include <gtest/gtest.h>
#include "employee.h"
#include "date.h"

TEST(Employee, Sample) {
  Employee employee(
      "Ivanov", "Ivan", Date(1, 9, 2019),
      Date(9, 10, 2019));
  ASSERT_EQ(employee.GetFullName(), "Ivanov Ivan");
  ASSERT_EQ(employee.ToString(),
            "Ivanov Ivan 01.09.2019 -> hired 09.10.2019");
  ASSERT_EQ(employee.GetAgeInYears(Date(10, 10, 2019)), 0);
  ASSERT_EQ(employee.GetAgeInYears(Date(10, 10, 2020)), 1);
  ASSERT_EQ(employee.GetTenureInDays(Date(11, 10, 2019)), 2);
  ASSERT_EQ(employee.GetTenureInDays(Date(11, 10, 2020)), 368);
}

TEST(Employee_1, Tests) {
  {
    Employee student("Nikita", "Baranov", Date(12, 4, 3),
                     Date(22, 7, 2200));
    EXPECT_EQ(student.GetFullName(), "Nikita Baranov");
    EXPECT_EQ(student.ToString(),
    "Nikita Baranov 12.04.0003 -> hired 22.07.2200");

    EXPECT_EQ(student.GetAgeInYears(Date(29, 2, 2019)), 2015);
    EXPECT_EQ(student.GetAgeInYears(Date(1, 1, 20)), 16);
    EXPECT_EQ(student.GetTenureInDays(Date(31, 12, 2019)), 0);
    EXPECT_EQ(student.GetTenureInDays(Date(11, 5, 2)), 0);
  }
  {
    Employee student("Nikita", "Shavnev", Date(27, 12, 3883),
                     Date(1, 7, 9999));
    EXPECT_EQ(student.GetFullName(), "Nikita Shavnev");
    EXPECT_EQ(student.ToString(),
              "Nikita Shavnev 27.12.3883 -> hired 01.07.9999");

    EXPECT_EQ(student.GetAgeInYears(Date(1, 1, 3992)), 108);
    EXPECT_EQ(student.GetAgeInYears(Date(1, 1, 239)), 0);
    EXPECT_EQ(student.GetTenureInDays(Date(31, 12, 2019)), 0);
    EXPECT_EQ(student.GetTenureInDays(Date(1, 12, 2)), 0);
  }
}