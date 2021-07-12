#ifndef PUGIXML_LOADER_ADAPTER_H
#define PUGIXML_LOADER_ADAPTER_H


#include "base_loader.h"


class pugixml_loader_adapter: public base_loader
{
    std::shared_ptr<std::vector<department>> load(
            std::string const& filename) override;
    void save(std::string const& filename,
              std::shared_ptr<std::vector<department>> departments) override;
};


#endif // PUGIXML_LOADER_ADAPTER_H
