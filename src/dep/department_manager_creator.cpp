#include "department_manager_creator.h"


std::shared_ptr<department_manager> department_manager_creator::get_manager()
{
    if (!man_ptr_)
        _create_manager();

    return man_ptr_;
}

void department_manager_creator::_create_manager()
{
    static auto man_ptr = std::make_shared<department_manager>();
    man_ptr_ = man_ptr;
}
