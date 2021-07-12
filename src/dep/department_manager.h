#ifndef DEPARTMENT_MANAGER_H
#define DEPARTMENT_MANAGER_H


#include <vector>

#include "base_manager.h"
#include "department.hpp"


class department_manager: base_manager
{
public:
    std::shared_ptr<std::vector<department>> get_departments() const;
    void set_departments_ptr(
            std::shared_ptr<std::vector<department>> new_departments);

private:
    std::shared_ptr<std::vector<department>> departments_;
};

#endif // DEPARTMENT_MANAGER_H
