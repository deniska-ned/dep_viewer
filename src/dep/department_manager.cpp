#include "department_manager.h"


std::vector<department> department_manager::get_departments() const
{
    return _departments;
}

void department_manager::set_departments(
        std::vector<department> const& new_departments)
{
    _departments = new_departments;
}
