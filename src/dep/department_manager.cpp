#include <memory>
#include "department_manager.h"


std::shared_ptr<std::vector<department>> department_manager::get_departments() const
{
    return departments_;
}

void department_manager::set_departments_ptr(
        std::shared_ptr<std::vector<department>> new_departments)
{
    departments_ = new_departments;
}
