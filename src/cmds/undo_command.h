#ifndef UNDO_COMMAND_H
#define UNDO_COMMAND_H


#include "base_command.h"


class undo_command: public base_command
{
public:
    bool execute() override;
    std::shared_ptr<base_command> clone() override;
};

#endif // UNDO_COMMAND_H
