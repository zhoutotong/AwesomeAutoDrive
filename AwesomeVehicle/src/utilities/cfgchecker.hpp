#pragma once
#include <iostream>
#include <yaml-cpp/yaml.h>

#include "aexception.hpp"

namespace awe
{
class CfgChecker
{

public:
    static void nodeIsOk(const YAML::Node &n);
    static void nodeIsDefAndSequence(const YAML::Node &n);
};
} // namespace awe
