#pragma once

#include <iostream>

#include "utilities/typedef.hpp"
#include "vehicle.hpp"
#include "vehicle_manager.hpp"

namespace awesomevehicle
{
VehicleFactory
{
    explicit VehicleFactory();
    ~VehicleFactory();

    Vehicle& createVehicle(const AString &name);
    Vehicle& createVehicle(const AString &name, const AString &cfgFile);

};
} // namespace awesomevehicle
