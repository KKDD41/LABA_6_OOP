#include <iostream>
#include "date.h"
#include <fstream>

// HELP FUNCTIONS

int JDN_system(const Date& date) {
  int a = (14 - date.month) / 12;
  int y = 4800 + date.year - a;
  int m = date.month + 12 * a - 3;
  int JDN =
      date.day + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400
          - 32045;
  return JDN;
}

int NumberOfDaysInMonth(const Date& date) {
  switch (date.month) {
    case 2: {
      if (IsLeap(date)) {
        return 29;
      }
      return 28;
    }
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12: {
      return 31;
    }
    case 4:
    case 6:
    case 9:
    case 11: {
      return 30;
    }
  }
  return 0;
}

bool IsLeap(const Date& date) {
  if (((date.year % 4 == 0) && (date.year % 100 != 0))
                            || date.year % 400 == 0) {
    return true;
  }
  return false;
}

Date NextDate(const Date& date) {
  if (date.day <= NumberOfDaysInMonth(date) - 1) {
    Date new_date(date.day + 1, date.month, date.year);
    return new_date;
  }
  if (date.month == 12) {
    Date new_date(1, 1, (date.year + 1) % 10'000);
    return new_date;
  }
  Date new_date(1, date.month + 1, date.year);
  return new_date;
}

Date PreviousDate(const Date& date) {
  if (date.day > 1) {
    Date new_date(date.day - 1, date.month, date.year);
    return new_date;
  }
  if (date.month == 1) {
    Date new_date(31, 12, date.year - 1);
    return new_date;
  }
  Date new_date(0, date.month - 1, date.year);
  new_date.day = NumberOfDaysInMonth(new_date);
  return new_date;
}


// STRING-DATE PROCESSING

std::string DateToString(const Date& date) {
  std::string day_str = std::to_string(date.day);
  std::string month_str = std::to_string(date.month);
  std::string year_str = std::to_string(date.year);
  if (day_str.size() == 1) {
    day_str = '0' + day_str;
  }
  if (month_str.size() == 1) {
    month_str = '0' + month_str;
  }
  for (int i = 0; year_str.size() < 4; i++) {
    year_str = '0' + year_str;
  }
  return day_str + "." + month_str + "." + year_str;
}

void ProcessDates(const std::string& input_file_name,
                  const std::string& output_file_name) {
  std::ifstream read(input_file_name);
  int num_of_dates;
  read >> num_of_dates;

  std::ofstream write(output_file_name);
  for (int i = 0; i < num_of_dates; i++) {
    Date date;
    read >> date.day >> date.month >> date.year;
    write << DateToString(PreviousDate(date)) << " "
          << DateToString(NextDate(date)) << "\n";
  }
  read.close();
  write.close();
}

// OPERATORS

bool Date::operator==(const Date& rhs) const {
  return (day == rhs.day) && (month == rhs.month) && (year == rhs.year);
}

bool Date::operator<(const Date& rhs) const {
  if (year != rhs.year) {
    return year < rhs.year;
  }
  if (month != rhs.month) {
    return month < rhs.month;
  }
  return day < rhs.day;
}
