#include "load_command.h"

#include "load_manager_creator.h"
#include "department_manager_creator.h"


bool load_command::execute()
{
    bool res = false;

    std::string filename = _tableowner->get_load_filename();

    if (filename.empty()) {
        _tableowner->show_message("File is not selected");
        res = false;
    }
    else
    {
        _tableowner->set_save_filename(filename);

        std::shared_ptr<std::vector<department>> tdata;
        tdata = load_manager_creator().get_manager()->load(filename);

        department_manager_creator().get_manager()->set_departments_ptr(tdata);

        _tableowner->set_table_data(tdata);

        _make_backup();

        res = true;
    }

    return res;
}

std::shared_ptr<base_command> load_command::clone()
{
    return std::make_shared<load_command>(*this);
}
