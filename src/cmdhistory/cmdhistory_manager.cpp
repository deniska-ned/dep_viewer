#include "cmdhistory_manager.h"


void cmdhistory_manager::add_new(std::shared_ptr<base_command> cmd)
{
    std::shared_ptr<base_command> cmd_clone = cmd->clone();

    if (_it != _deque.end())
    {
        _deque.erase(_it + 1, _deque.end());
    }

    _deque.push_back(cmd_clone);

    _it = _deque.end() - 1;
}

bool cmdhistory_manager::has_prev()
{
    return _it != _deque.begin();
}

void cmdhistory_manager::goto_prev()
{
    // TODO: add throwing exception
    --_it;
    (*_it)->undo();
}

bool cmdhistory_manager::has_next()
{
    return _it != _deque.end();
}

void cmdhistory_manager::goto_next()
{
    // TODO: add throwing exception
    ++_it;
    (*_it)->undo();
}
