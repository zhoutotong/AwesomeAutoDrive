#pragma once

#include <iostream>
#include <exception>

#include "typedef.hpp"


namespace awe
{
class AException : public std::exception
{
public:
    explicit AException(const AString &reason);
    ~AException();

    const char* what()const noexcept override { return mWhat.c_str(); };

private:
    const AString mWhat;
};
} // namespace awe
