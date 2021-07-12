#ifndef I_TABLEOWNER_H
#define I_TABLEOWNER_H


#include <string>

#include "department.hpp"


class i_tableowner
{
public:
    virtual std::shared_ptr<std::vector<department>> get_table_data() = 0;
    virtual void set_table_data(
            std::shared_ptr<std::vector<department>> departments) = 0;

    virtual std::string get_load_filename() = 0;

    virtual std::string get_save_filename() = 0;
    virtual void set_save_filename(std::string const& filename) = 0;

    virtual void show_message(std::string const& mes) = 0;
};

#endif // I_TABLEOWNER_H

