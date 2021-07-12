#include "employment.h"

employment::employment(std::string const& surname, std::string const& name,
        std::string const& middle_name, std::string const& function,
        int const salary)
    : surname_(surname), name_(name), middle_name_(middle_name),
      function_(function), salary_(salary)
{}

std::string employment::surname() const
{
    return surname_;
}

void employment::set_surname(std::string const& new_surname)
{
    surname_ = new_surname;
}

std::string employment::name() const
{
    return name_;
}

void employment::set_name(std::string const& new_name)
{
    name_ = new_name;
}

std::string employment::middle_name() const
{
    return middle_name_;
}

void employment::set_middle_name(std::string const& new_middle_name)
{
    middle_name_ = new_middle_name;
}

std::string employment::function() const
{
    return function_;
}

void employment::set_function(std::string const& new_function)
{
    function_ = new_function;
}

int employment::salary() const
{
    return salary_;
}

void employment::set_salary(int new_salary)
{
    salary_ = new_salary;
}
