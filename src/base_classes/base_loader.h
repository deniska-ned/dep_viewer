#ifndef BASE_LOADER_H
#define BASE_LOADER_H


#include <memory>
#include <vector>

#include "department.hpp"


class base_loader
{
public:
    virtual std::shared_ptr<std::vector<department>> load(std::string const& filename) = 0;
    virtual void save(std::string const& filename,
                      std::shared_ptr<std::vector<department>> departments) = 0;
};


#endif // BASE_LOADER_H
