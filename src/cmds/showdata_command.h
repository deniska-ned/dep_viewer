#ifndef SHOWDATA_COMMAND_H
#define SHOWDATA_COMMAND_H


#include "base_command.h"


class showdata_command: public base_command
{
public:
    bool execute() override;
    std::shared_ptr<base_command> clone() override;
};

#endif // SHOWDATA_COMMAND_H
