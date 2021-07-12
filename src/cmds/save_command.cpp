#include "save_command.h"

#include "department_manager_creator.h"
#include "load_manager_creator.h"


bool save_command::execute()
{
    std::string filename = _tableowner->get_save_filename();

    auto tdata = _tableowner->get_table_data();
    load_manager_creator().get_manager()->save(filename, tdata);

    return false;
}

std::shared_ptr<base_command> save_command::clone()
{
    return std::make_shared<save_command>(*this);
}
