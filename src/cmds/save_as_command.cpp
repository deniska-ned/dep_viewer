#include "save_as_command.h"

#include "load_manager_creator.h"


bool save_as_command::execute()
{
    std::string filename = tableowner_->get_new_save_filename();

    if (filename.empty())
    {
        tableowner_->show_message("Save file name is not selected");
    }
    else
    {
        tableowner_->set_opened_filename(filename);
        auto tdata = tableowner_->get_table_data();
        load_manager_creator().get_manager()->save(filename, tdata);
    }

    return false;
}

std::shared_ptr<base_command> save_as_command::clone()
{
    return std::make_shared<save_as_command>(*this);
}
