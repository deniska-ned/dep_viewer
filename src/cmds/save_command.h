#ifndef SAVE_COMMAND_H
#define SAVE_COMMAND_H


#include "base_command.h"


class save_command: public base_command
{
public:
    bool execute() override;
    std::shared_ptr<base_command> clone() override;
};

#endif // SAVE_COMMAND_H
