#include "update_command.h"

#include "department_manager_creator.h"


bool update_command::execute()
{
    auto tdata = _tableowner->get_table_data();
    department_manager_creator().get_manager()->set_departments_ptr(tdata);

    _make_backup();

    return true;
}

std::shared_ptr<base_command> update_command::clone()
{
    return std::make_shared<update_command>(*this);
}
