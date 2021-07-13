#include "save_command.h"

#include "department_manager_creator.h"
#include "load_manager_creator.h"


bool save_command::execute()
{
    std::string filename = tableowner_->get_opened_filename();

    if (filename.empty())
    {
        filename = tableowner_->get_new_save_filename();
    }

    if (filename.empty())
    {
        tableowner_->show_message("Save file name is not selected");
    }
    else
    {
        auto tdata = tableowner_->get_table_data();
        load_manager_creator().get_manager()->save(filename, tdata);
    }

    return false;
}

std::shared_ptr<base_command> save_command::clone()
{
    return std::make_shared<save_command>(*this);
}
