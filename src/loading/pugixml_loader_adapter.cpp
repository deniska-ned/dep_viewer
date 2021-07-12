#include "pugixml_loader_adapter.h"

#include "pugixml.hpp"


std::shared_ptr<std::vector<department>> pugixml_loader_adapter::load(
        std::string const& filename)
{
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(filename.c_str());

    if (!result)
    {
        int a = 10;
        // TODO: add result check
    }

    auto departments_ptr = std::make_shared<std::vector<department>>();

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

        departments_ptr->push_back(dep);
    }

    return departments_ptr;
}

void pugixml_loader_adapter::save(std::string const& filename,
                                  std::shared_ptr<std::vector<department>> departments)
{
    pugi::xml_document doc;

    pugi::xml_node deps_node = doc.append_child("departments");

    for (auto const& dep: *departments)
    {
        pugi::xml_node dep_node = deps_node.append_child("department");

        dep_node.append_attribute("name") = dep.name().c_str();

        pugi::xml_node emps_node = dep_node.append_child("employments");

        for (auto const& emp: dep.get_employments())
        {
            pugi::xml_node emp_node = emps_node.append_child("employment");

            emp_node.append_child("surname").text() = emp.surname().c_str();
            emp_node.append_child("name").text() = emp.name().c_str();
            emp_node.append_child("middleName").text() = emp.middle_name().c_str();
            emp_node.append_child("function").text() = emp.function().c_str();
            emp_node.append_child("salary").text() = std::to_string(emp.salary()).c_str();
        }
    }

    pugi::xml_node decl = doc.prepend_child(pugi::node_declaration);
    decl.append_attribute("version") = "1.0";
    decl.append_attribute("encoding") = "UTF-8";

    doc.save_file(filename.c_str(), "   ", pugi::format_default,
                  pugi::encoding_utf8);
}
