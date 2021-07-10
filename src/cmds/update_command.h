#ifndef UPDATE_COMMAND_H
#define UPDATE_COMMAND_H


#include "base_command.h"


class update_command: public base_command
{
public:
    using base_command::base_command;

    bool execute() override;
    std::shared_ptr<base_command> clone() override;
};

#endif // UPDATE_COMMAND_H
