#include "department.hpp"
#include <stdexcept>


department::department(std::string const& name)
    : name_(name)
{ }

std::string department::name() const
{
    return name_;
}

void department::set_name(std::string const& new_name)
{
    name_ = new_name;
}

std::size_t department::employment_count() const
{
    return employments_.size();
}

double department::avg_salary() const
{
    return avg_salary_;
}

employment department::get_employment(std::size_t index) const
{
    return employments_.at(index);
}

std::vector<employment> const& department::get_employments() const
{
    return employments_;
}

void department::append_employment(employment const& new_employment)
{
    employments_.push_back(new_employment);

    avg_salary_app_emp(new_employment.salary(), employments_.size());
}

void department::remove_employment(std::size_t index)
{
    if (index >= employments_.size())
        throw std::out_of_range("remove employment index out of range");

    auto it = employments_.begin();
    advance(it, index);

    int emp_salary = it->salary();

    employments_.erase(it);

    avg_salary_rem_emp(emp_salary, employments_.size());
}

void department::avg_salary_update()
{
    if (employments_.empty())
    {
        avg_salary_ = 0.0;
    }
    else
    {
        double sum_salary = 0.0;

        for (employment const& emp: employments_)
            sum_salary += emp.salary();

        avg_salary_ = sum_salary / employments_.size();
    }
}

void department::avg_salary_rem_emp(int his_salary,
                                    std::size_t new_employment_count)
{
    if (0 == new_employment_count)
    {
        avg_salary_ = 0.0;
    }
    else
    {
        std::size_t old_employment_count = new_employment_count + 1;
        double old_sum_salary = avg_salary_ * old_employment_count;

        double new_sum_salary = old_sum_salary - his_salary;
        double new_avg_salary = new_sum_salary / new_employment_count;

        avg_salary_ = new_avg_salary;
    }
}

void department::avg_salary_app_emp(int his_salary,
                                    std::size_t new_employment_count)
{
    std::size_t old_employment_count = new_employment_count - 1;
    double old_sum_salary = avg_salary_ * old_employment_count;

    double new_sum_salary = old_sum_salary + his_salary;
    double new_avg_salary = new_sum_salary / new_employment_count;

    avg_salary_ = new_avg_salary;
}
