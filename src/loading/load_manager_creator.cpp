#include "load_manager_creator.h"


std::shared_ptr<load_manager> load_manager_creator::get_manager()
{
    if (!_man_ptr)
    {
        _create_manager();
    }

    return _man_ptr;
}

void load_manager_creator::_create_manager()
{
    static auto man_ptr = std::make_shared<load_manager>();
    _man_ptr = man_ptr;
}
