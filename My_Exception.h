#pragma once
#include <stdexcept>


class My_Exception: public std::logic_error
{
    public:
        My_Exception(const char *s);
        ~My_Exception();
};
