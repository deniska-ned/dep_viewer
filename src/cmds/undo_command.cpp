#include "undo_command.h"

#include "cmdhistory_manager_creator.h"


bool undo_command::execute()
{
    auto ch_man_ptr = cmdhistory_manager_creator().get_manager();

    if (!ch_man_ptr->has_prev())
    {
        _tableowner->show_message("Cannot go back any more");
    }
    else
    {
        ch_man_ptr->goto_prev();
    }

    return false;
}

std::shared_ptr<base_command> undo_command::clone()
{
    return std::make_shared<undo_command>(*this);
}
