#include "load_command.h"

#include "load_manager_creator.h"
#include "department_manager_creator.h"


bool load_command::execute()
{
    bool res = false;

    std::string filename = tableowner_->get_new_open_filename();

    if (filename.empty()) {
        tableowner_->show_message("File is not selected");
        res = false;
    }
    else
    {
        tableowner_->set_opened_filename(filename);

        std::shared_ptr<std::vector<department>> tdata;
        tdata = load_manager_creator().get_manager()->load(filename);

        tableowner_->set_table_data(tdata);

        make_backup();

        res = true;
    }

    return res;
}

std::shared_ptr<base_command> load_command::clone()
{
    return std::make_shared<load_command>(*this);
}
