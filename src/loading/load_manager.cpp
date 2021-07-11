#include "load_manager.h"

std::shared_ptr<std::vector<department>> load_manager::load(std::string const& filename) const
{
    return _loader_ptr->load(filename);
}

void load_manager::save(std::string const& filename,
                        std::shared_ptr<std::vector<department>> departments) const
{
    _loader_ptr->save(filename, departments);
}
