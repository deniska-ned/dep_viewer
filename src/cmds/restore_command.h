#ifndef RESTORE_COMMAND_H
#define RESTORE_COMMAND_H


#include "base_command.h"


class restore_command: public base_command
{
public:
    using base_command::base_command;

    bool execute() override;
    std::shared_ptr<base_command> clone() override;
};

#endif // RESTORE_COMMAND_H
