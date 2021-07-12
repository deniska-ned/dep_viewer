#include "save_command.h"

#include "department_manager_creator.h"
#include "load_manager_creator.h"


bool save_command::execute()
{
    std::string filename = tableowner_->get_save_filename();

    if (filename.empty())
    {
        tableowner_->show_message("Load file first");
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
