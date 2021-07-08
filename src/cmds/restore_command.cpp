#include "restore_command.h"

#include "cmdhistory_manager_creator.h"


bool restore_command::execute()
{
    auto ch_man_ptr = cmdhistory_manager_creator().get_manager();

    if (!ch_man_ptr->has_next())
    {
        _tableowner->show_message("Cannot go forward any more");
    }
    else
    {
        ch_man_ptr->goto_next();
    }

    return false;
}

std::shared_ptr<base_command> restore_command::clone()
{
    return std::make_shared<restore_command>(*this);
}
