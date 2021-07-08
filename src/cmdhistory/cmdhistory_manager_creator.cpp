#include "cmdhistory_manager_creator.h"


std::shared_ptr<cmdhistory_manager> cmdhistory_manager_creator::get_manager()
{
    if (!_man_ptr)
        _create_manager();

    return _man_ptr;
}

void cmdhistory_manager_creator::_create_manager()
{
    static auto man_ptr = std::make_shared<cmdhistory_manager>();
    _man_ptr = man_ptr;
}
