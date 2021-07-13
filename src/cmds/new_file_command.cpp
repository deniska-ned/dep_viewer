#include "new_file_command.h"

#include "cmdhistory_manager_creator.h"


bool new_file_command::execute()
{
    cmdhistory_manager_creator().get_manager()->clear_history();

    auto tdata = std::make_shared<std::vector<department>>();

    tableowner_->set_opened_filename("");
    tableowner_->set_table_data(tdata);

    make_backup();

    return true;
}

std::shared_ptr<base_command> new_file_command::clone()
{
    return std::make_shared<new_file_command>(*this);
}
