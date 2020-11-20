#include "date.h"
#include <string>

#ifndef EMPLOYEE_H_
#define EMPLOYEE_H_

class Employee {
 public:
  Employee(const std::string& name, const std::string& last,
           const Date& birth, const Date& hire);

  std::string GetFullName() const;

  std::string ToString() const;

  int GetAgeInYears(const Date&) const;

  int GetTenureInDays(const Date&) const;

 private:
  std::string first_name_{"John"};
  std::string last_name_{"Doe"};
  Date birth_date_ = Date(12, 3, 2003);
  Date hiring_date_ = Date(12, 3, 2003);
};


#endif  // EMPLOYEE_H_
