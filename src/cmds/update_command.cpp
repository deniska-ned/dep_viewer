#include "update_command.h"

#include "department_manager_creator.h"


bool update_command::execute()
{
    std::vector<department> tdata = _tableowner->get_table_data();
    department_manager_creator().get_manager()->set_departments(tdata);

    return false;
}

std::shared_ptr<base_command> update_command::clone()
{
    return std::make_shared<update_command>(*this);
}
