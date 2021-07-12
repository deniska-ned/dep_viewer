#include "base_command.h"

#include "department_manager_creator.h"


base_command::base_command(i_tableowner *tableowner)
    : tableowner_(tableowner)
{}

base_command::~base_command()
{}

void base_command::undo()
{
    tableowner_->set_table_data(snapshot_);
}

void base_command::make_backup()
{
    snapshot_ = std::make_shared<std::vector<department>>(*tableowner_->get_table_data());
}
