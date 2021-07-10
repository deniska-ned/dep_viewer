#include "pugixml_loader_adapter.h"

#include "pugixml.hpp"


std::vector<department> pugixml_loader_adapter::load(
        std::string const& filename)
{
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(filename.c_str());

    if (!result)
    {
        int a = 10;
        // TODO: add result check
    }

    std::vector<department> departments;

    auto dep_nodes = doc.child("departments").children("department");

    for (pugi::xml_node const& dep_node: dep_nodes)
    {
        std::vector<employment> dep_empls;

        auto empl_nodes = dep_node.child("employments").children("employment");

        for (pugi::xml_node const& empl_node: empl_nodes)
        {
            std::string surname = empl_node.child("surname").child_value();
            std::string name = empl_node.child("name").child_value();
            std::string middle_name = \
            empl_node.child("middleName").child_value();
            std::string function = empl_node.child("function").child_value();
            std::string salary_str = empl_node.child("salary").child_value();
            int salary = stoi(salary_str);

            dep_empls.emplace_back(surname, name, middle_name,
                                   function, salary);
        }

        std::string dep_name = dep_node.attribute("name").value();
        department dep(dep_name);
        dep.replace_employments(dep_empls.begin(), dep_empls.end());

        departments.push_back(dep);
    }

    return departments;
}

void pugixml_loader_adapter::save(std::string const& filename,
                                  std::vector<department> const& departments)
{
    // TODO: implement saving
}
