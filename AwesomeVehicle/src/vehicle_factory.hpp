#pragma once

#include <iostream>

// yaml 头文件
#include <yaml-cpp/yaml.h>

#include "utilities/typedef.hpp"
#include "vehicle.hpp"
#include "vehicle_manager.hpp"

#include "aexception.hpp"

namespace awe
{
class VehicleFactory
{
public:
    explicit VehicleFactory();
    ~VehicleFactory();

    void produceVehicle(const AString &name, const AString &cfgFile, Vehicle::VehicleUniquePtr &vehicle);

};
} // namespace awe
