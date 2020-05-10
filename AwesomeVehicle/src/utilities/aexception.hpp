#pragma once

#include <iostream>
#include <exception>

#include "utilities/typedef.hpp"


namespace awesomevehicle
{
AException : public std::exception
{
public:
    explicit AException();
    ~AException();

    const AString &what();
};
} // namespace awesomevehicle
