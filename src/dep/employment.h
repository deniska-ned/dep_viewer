#ifndef EMPLOYMENT_H
#define EMPLOYMENT_H


#include <string>


class employment
{
public:
    employment(std::string const& surname, std::string const& name,
            std::string const& middle_name, std::string const& function,
            int const salary);

    std::string surname() const;
    void set_surname(std::string const& new_surname);

    std::string name() const;
    void set_name(std::string const& new_name);

    std::string middle_name() const;
    void set_middle_name(std::string const& new_middle_name);

    std::string function() const;
    void set_function(std::string const& new_function);

    int salary() const;
    void set_salary(int const new_salary);

private:
    std::string surname_;
    std::string name_;
    std::string middle_name_;
    std::string function_;
    int salary_;
};

#endif // EMPLOYMENT_H
