#ifndef LOAD_MANAGER_CREATOR_H
#define LOAD_MANAGER_CREATOR_H


#include <memory>

#include "load_manager.h"


class load_manager_creator
{
public:
    std::shared_ptr<load_manager> get_manager();

private:
    std::shared_ptr<load_manager> man_ptr_;

    void create_manager();
};

#endif // LOAD_MANAGER_CREATOR_H
