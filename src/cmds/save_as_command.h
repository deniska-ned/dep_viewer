#ifndef SAVE_AS_COMMAND_H
#define SAVE_AS_COMMAND_H


#include "base_command.h"


class save_as_command: public base_command
{
public:
    using base_command::base_command;

    bool execute() override;
    std::shared_ptr<base_command> clone() override;
};


#endif // SAVE_AS_COMMAND_H
