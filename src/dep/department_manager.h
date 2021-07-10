#ifndef DEPARTMENT_MANAGER_H
#define DEPARTMENT_MANAGER_H


#include <vector>

#include "base_manager.h"
#include "department.hpp"


class department_manager: base_manager
{
public:
    std::vector<department> get_departments() const;
    void set_departments(std::vector<department> const& new_departments);

private:
    std::vector<department> _departments;
};

#endif // DEPARTMENT_MANAGER_H
