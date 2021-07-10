#include "base_command.h"

#include "department_manager_creator.h"


base_command::base_command(i_tableowner *tableowner)
    : _tableowner(tableowner)
{}

base_command::~base_command()
{}

void base_command::undo()
{
    _tableowner->set_table_data(_snapshot);
    department_manager_creator().get_manager()->set_departments(_snapshot);
}

void base_command::_make_backup()
{
    _snapshot = _tableowner->get_table_data();
}
