#include "cmdhistory_manager.h"


void cmdhistory_manager::add_new(std::shared_ptr<base_command> cmd)
{
    std::shared_ptr<base_command> cmd_clone = cmd->clone();

    auto next_it = _deque.begin();
    advance(next_it, next_i);
    _deque.erase(next_it, _deque.end());

    _deque.push_back(cmd_clone);
    ++next_i;
}

bool cmdhistory_manager::has_prev()
{
    return next_i > 1;
}

void cmdhistory_manager::goto_prev()
{
    // TODO: add throwing exception
    --next_i;
    _deque[next_i - 1]->undo();
}

bool cmdhistory_manager::has_next()
{
    return next_i != _deque.size();
}

void cmdhistory_manager::goto_next()
{
    // TODO: add throwing exception
    ++next_i;
    _deque[next_i - 1]->undo();
}
