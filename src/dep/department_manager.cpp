#include <memory>
#include "department_manager.h"


std::shared_ptr<std::vector<department>> department_manager::get_departments() const
{
    return _departments;
}

void department_manager::set_departments_ptr(
        std::shared_ptr<std::vector<department>> new_departments)
{
    _departments = new_departments;
}
