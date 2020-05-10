#pragma once

#include <iostream>
#include <utility>
#include <map>
#include <vector>


namespace awe
{
using AString = std::string;

template<typename T1, typename T2>
using AMap = std::map<T1, T2>;

template<typename T1>
using AVector = std::vector<T1>;

} // namespace awe


