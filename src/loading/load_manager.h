#ifndef LOAD_MANAGER_H
#define LOAD_MANAGER_H


#include <memory>
#include <vector>

#include "department.hpp"
#include "base_loader.h"
#include "base_manager.h"
#include "pugixml_loader_adapter.h"


class load_manager: public base_manager
{
public:
    std::shared_ptr<std::vector<department>> load(std::string const& filename) const;
    void save(std::string const& filename,
              std::shared_ptr<std::vector<department>> departments) const;

private:
    std::shared_ptr<base_loader> _loader_ptr = \
    std::make_shared<pugixml_loader_adapter>();
};


#endif // LOAD_MANAGER_H
