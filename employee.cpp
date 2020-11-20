#include "employee.h"

std::string Employee::GetFullName() const {
  return first_name_ + " " + last_name_;
}

std::string Employee::ToString() const {
  return first_name_ + " " + last_name_ + " " + DateToString(birth_date_)
      + " -> hired " + DateToString(hiring_date_);
}

int Employee::GetAgeInYears(const Date& current_date) const {
  if (current_date < birth_date_) {
    return 0;
  }
  if (current_date.month > birth_date_.month
      || (current_date.month == birth_date_.month
          && current_date.day >= birth_date_.day)) {
    return current_date.year - birth_date_.year;
  }
  return current_date.year - birth_date_.year - 1;
}

int Employee::GetTenureInDays(const Date& current_date) const {
  if (current_date < hiring_date_) {
    return 0;
  }
  return JDN_system(current_date) - JDN_system(hiring_date_);
}

Employee::Employee(const std::string& name,
                   const std::string& last,
                   const Date& birth,
                   const Date& hire) {
  first_name_ = name;
  last_name_ = last;
  birth_date_.day = birth.day;
  birth_date_.month = birth.month;
  birth_date_.year = birth.year;
  hiring_date_.day = hire.day;
  hiring_date_.month = hire.month;
  hiring_date_.year = hire.year;
}



