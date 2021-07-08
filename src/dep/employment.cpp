#include "employment.h"

employment::employment(std::string const& surname, std::string const& name,
        std::string const& middle_name, std::string const& function,
        int const salary)
    : _surname(surname), _name(name), _middle_name(middle_name),
    _function(function), _salary(salary)
{}

std::string employment::surname() const
{
    return _surname;
}

void employment::set_surname(std::string const& new_surname)
{
    _surname = new_surname;
}

std::string employment::name() const
{
    return _name;
}

void employment::set_name(std::string const& new_name)
{
    _name = new_name;
}

std::string employment::middle_name() const
{
    return _middle_name;
}

void employment::set_middle_name(std::string const& new_middle_name)
{
    _middle_name = new_middle_name;
}

std::string employment::function() const
{
    return _function;
}

void employment::set_function(std::string const& new_function)
{
    _function = new_function;
}

int employment::salary() const
{
    return _salary;
}

void employment::set_salary(int new_salary)
{
    _salary = new_salary;
}
