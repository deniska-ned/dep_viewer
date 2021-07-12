#include "load_manager_creator.h"


std::shared_ptr<load_manager> load_manager_creator::get_manager()
{
    if (!man_ptr_)
    {
        create_manager();
    }

    return man_ptr_;
}

void load_manager_creator::create_manager()
{
    static auto man_ptr = std::make_shared<load_manager>();
    man_ptr_ = man_ptr;
}
