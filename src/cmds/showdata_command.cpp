#include "showdata_command.h"

#include "department_manager_creator.h"


bool showdata_command::execute()
{
    make_backup();

    auto tdata = department_manager_creator().get_manager()->get_departments();
    tableowner_->set_table_data(tdata);

    return true;
}

std::shared_ptr<base_command> showdata_command::clone()
{
    return std::make_shared<showdata_command>(*this);
}
