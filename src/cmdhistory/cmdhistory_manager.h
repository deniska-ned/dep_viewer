#ifndef CMDHISTORY_MANAGER_H
#define CMDHISTORY_MANAGER_H


#include <deque>
#include <memory>

#include "base_manager.h"
#include "base_command.h"


class cmdhistory_manager: base_manager
{
public:
    void add_new(std::shared_ptr<base_command> cmd);

    bool has_prev();
    void goto_prev();

    bool has_next();
    void goto_next();

private:
    std::deque<std::shared_ptr<base_command>> deque_;

    size_t next_i_ = 0;
};

#endif // CMDHISTORY_MANAGER_H
