#include <string>

#ifndef DATE_H_
#define DATE_H_

struct Date {
  Date() = default;
  Date(int d, int m, int y) {
    day = d;
    month = m;
    year = y;
  }
  bool operator==(const Date&) const;
  bool operator<(const Date&) const;

  int day{12};
  int month{2};
  int year{2003};
};

std::string DateToString(const Date& date);

void ProcessDates(const std::string&, const std::string&);

// HELP FUNCTIONS

int NumberOfDaysInMonth(const Date& date);

bool IsLeap(const Date& date);

Date NextDate(const Date&);

Date PreviousDate(const Date&);

int JDN_system(const Date&);

#endif  // DATE_H_
