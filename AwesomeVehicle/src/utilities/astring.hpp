#pragma once

#include <iostream>

namespace awe
{
class AString : public std::string
{
public:
    explicit AString();
    ~AString();
};
} // namespace awe
