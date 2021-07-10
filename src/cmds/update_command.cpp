#include "update_command.h"

#include "department_manager_creator.h"


bool update_command::execute()
{
    std::vector<department> tdata = _tableowner->get_table_data();
    department_manager_creator().get_manager()->set_departments(tdata);
    tdata = department_manager_creator().get_manager()->get_departments();
    _tableowner->set_table_data(tdata);

    _make_backup();

    return true;
}

std::shared_ptr<base_command> update_command::clone()
{
    return std::make_shared<update_command>(*this);
}
