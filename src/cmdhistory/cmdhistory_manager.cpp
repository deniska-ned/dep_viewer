#include "cmdhistory_manager.h"


void cmdhistory_manager::add_new(std::shared_ptr<base_command> cmd)
{
    std::shared_ptr<base_command> cmd_clone = cmd->clone();

    auto next_it = deque_.begin();
    advance(next_it, next_i_);
    deque_.erase(next_it, deque_.end());

    deque_.push_back(cmd_clone);
    ++next_i_;
}

bool cmdhistory_manager::has_prev()
{
    return next_i_ > 1;
}

void cmdhistory_manager::goto_prev()
{
    // TODO: add throwing exception
    --next_i_;
    deque_[next_i_ - 1]->undo();
}

bool cmdhistory_manager::has_next()
{
    return next_i_ != deque_.size();
}

void cmdhistory_manager::goto_next()
{
    // TODO: add throwing exception
    ++next_i_;
    deque_[next_i_ - 1]->undo();
}
