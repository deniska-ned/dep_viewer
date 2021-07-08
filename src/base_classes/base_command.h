#ifndef BASE_COMMAND_H
#define BASE_COMMAND_H


#include <memory>

#include "i_tableowner.h"


class base_command
{
public:
    base_command(std::shared_ptr<i_tableowner> tableowner);

    virtual ~base_command() = 0;

    /**
     * @return true if changes data for storing in history, otherwise false
     */
    virtual bool execute() = 0;

    virtual std::shared_ptr<base_command> clone() = 0;

    virtual void undo();

protected:
    std::shared_ptr<i_tableowner> _tableowner;
    std::vector<department> _snapshot;

    virtual void _make_backup();
};

#endif // BASE_COMMAND_H
