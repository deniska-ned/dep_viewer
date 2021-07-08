#include "load_command.h"

#include "load_manager_creator.h"
#include "department_manager_creator.h"


bool load_command::execute()
{
    _make_backup();

    std::string filename = _tableowner->get_load_filename();

    std::vector<department> tdata;
    tdata = load_manager_creator().get_manager()->load(filename);

    department_manager_creator().get_manager()->set_departments(tdata);

    _tableowner->set_table_data(tdata);

    return true;
}

std::shared_ptr<base_command> load_command::clone()
{
    return std::make_shared<load_command>(*this);
}
