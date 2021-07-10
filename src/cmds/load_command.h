#ifndef LOAD_COMMAND_H
#define LOAD_COMMAND_H


#include "base_command.h"


class load_command: public base_command
{
public:
    using base_command::base_command;

    bool execute() override;
    std::shared_ptr<base_command> clone() override;
};

#endif // LOAD_COMMAND_H
