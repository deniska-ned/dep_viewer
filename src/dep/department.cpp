#include "department.hpp"
#include <stdexcept>


department::department(std::string const& name)
    : _name(name)
{ }

std::string department::name() const
{
    return _name;
}

void department::set_name(std::string const& new_name)
{
    _name = new_name;
}

std::size_t department::employment_count() const
{
    return _employments.size();
}

double department::avg_salary() const
{
    return _avg_salary;
}

employment department::get_employment(std::size_t index) const
{
    return _employments.at(index);
}

void department::append_employment(employment const& new_employment)
{
    _employments.push_back(new_employment);

    _avg_salary_app_emp(new_employment.salary(), _employments.size());
}

void department::remove_employment(std::size_t index)
{
    if (index >= _employments.size())
        throw std::out_of_range("remove employment index out of range");

    auto it = _employments.begin();
    advance(it, index);

    int emp_salary = it->salary();

    _employments.erase(it);

    _avg_salary_rem_emp(emp_salary, _employments.size());
}

void department::_avg_salary_update()
{
    if (_employments.empty())
    {
        _avg_salary = 0.0;
    }
    else
    {
        double sum_salary = 0.0;

        for (employment const& emp: _employments)
            sum_salary += emp.salary();

        _avg_salary = sum_salary / _employments.size();
    }
}

void department::_avg_salary_rem_emp(int his_salary,
        std::size_t new_employment_count)
{
    if (0 == new_employment_count)
    {
        _avg_salary = 0.0;
    }
    else
    {
        std::size_t old_employment_count = new_employment_count + 1;
        double old_sum_salary = _avg_salary * old_employment_count;

        double new_sum_salary = old_sum_salary - his_salary;
        double new_avg_salary = new_sum_salary / new_employment_count;

        _avg_salary = new_avg_salary;
    }
}

void department::_avg_salary_app_emp(int his_salary,
        std::size_t new_employment_count)
{
    std::size_t old_employment_count = new_employment_count - 1;
    double old_sum_salary = _avg_salary * old_employment_count;

    double new_sum_salary = old_sum_salary + his_salary;
    double new_avg_salary = new_sum_salary / new_employment_count;

    _avg_salary = new_avg_salary;
}
