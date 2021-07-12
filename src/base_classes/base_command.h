#ifndef BASE_COMMAND_H
#define BASE_COMMAND_H


#include <memory>

#include "i_tableowner.h"


class base_command
{
public:
    explicit base_command(i_tableowner *tableowner);

    virtual ~base_command() = 0;

    /**
     * @return true if changes data for storing in history, otherwise false
     */
    virtual bool execute() = 0;

    virtual std::shared_ptr<base_command> clone() = 0;

    virtual void undo();

protected:
    i_tableowner *tableowner_;
    std::shared_ptr<std::vector<department>> snapshot_;

    virtual void make_backup();
};

#endif // BASE_COMMAND_H
