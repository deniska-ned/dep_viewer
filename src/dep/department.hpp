#ifndef DEPARTMENT_H
#define DEPARTMENT_H


#include <vector>

#include "employment.h"


class department
{
public:
    explicit department(std::string const& name);

    std::string name() const;
    void set_name(std::string const& new_name);

    std::size_t employment_count() const;

    double avg_salary() const;

    employment get_employment(std::size_t index) const;
    std::vector<employment> const& get_employments() const;
    void append_employment(employment const& new_employment);
    void remove_employment(std::size_t index);

    template<class InputIt>
    void replace_employments(InputIt begin, InputIt end);

private:
    std::string name_;
    double avg_salary_ = 0.0;
    std::vector<employment> employments_;

    void avg_salary_update();
    void avg_salary_rem_emp(int his_salary, std::size_t new_employment_count);
    void avg_salary_app_emp(int his_salary, std::size_t new_employment_count);
};

template<class InputIt>
void department::replace_employments(InputIt begin, InputIt end)
{
    employments_.clear();

    for (InputIt it = begin; it != end; ++it)
        employments_.push_back(*it);

    avg_salary_update();
}

#endif // DEPARTMENT_H
