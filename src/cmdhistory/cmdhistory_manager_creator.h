#ifndef CMDHISTORY_MANAGER_CREATOR_H
#define CMDHISTORY_MANAGER_CREATOR_H

#include <memory>

#include "cmdhistory_manager.h"


class cmdhistory_manager_creator
{
public:
    std::shared_ptr<cmdhistory_manager> get_manager();

private:
    std::shared_ptr<cmdhistory_manager> _man_ptr;

    void _create_manager();
};



#endif // CMDHISTORY_MANAGER_CREATOR_H
