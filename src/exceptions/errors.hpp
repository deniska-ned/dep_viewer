#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <stdexcept>
#include <exception>


class app_base_error: public std::exception
{
};

class app_filename_not_selected: app_base_error
{
};

class app_table_not_loaded: app_base_error
{
};

#endif //ERRORS_HPP
