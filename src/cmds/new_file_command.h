#ifndef NEW_FILE_COMMAND_H
#define NEW_FILE_COMMAND_H

#include "base_command.h"


class new_file_command: public base_command
{
public:
    using base_command::base_command;

    bool execute() override;
    std::shared_ptr<base_command> clone() override;
};


#endif // NEW_FILE_COMMAND_H
