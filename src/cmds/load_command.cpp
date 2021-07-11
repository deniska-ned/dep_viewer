#include "load_command.h"

#include "load_manager_creator.h"
#include "department_manager_creator.h"


bool load_command::execute()
{
    std::string filename = _tableowner->get_load_filename();

    std::shared_ptr<std::vector<department>> tdata;
    tdata = load_manager_creator().get_manager()->load(filename);

    department_manager_creator().get_manager()->set_departments_ptr(tdata);

    _tableowner->set_table_data(tdata);

    _make_backup();

    return true;
}

std::shared_ptr<base_command> load_command::clone()
{
    return std::make_shared<load_command>(*this);
}
