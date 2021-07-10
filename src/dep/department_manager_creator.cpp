#include "department_manager_creator.h"


std::shared_ptr<department_manager> department_manager_creator::get_manager()
{
    if (!_man_ptr)
        _create_manager();

    return _man_ptr;
}

void department_manager_creator::_create_manager()
{
    static auto man_ptr = std::make_shared<department_manager>();
    _man_ptr = man_ptr;
}
