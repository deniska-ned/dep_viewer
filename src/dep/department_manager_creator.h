#ifndef DEPARTMENT_MANAGER_CREATOR_H
#define DEPARTMENT_MANAGER_CREATOR_H


#include <memory>

#include "department_manager.h"


class department_manager_creator
{
public:
    std::shared_ptr<department_manager> get_manager();

private:
    std::shared_ptr<department_manager> man_ptr_;

    void _create_manager();
};

#endif // DEPARTMENT_MANAGER_CREATOR_H
