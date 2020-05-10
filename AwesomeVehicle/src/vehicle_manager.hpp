#pragma once

#include <iostream>

#include "vehicle.hpp"
#include "typedef.hpp"

namespace vehicleawesome
{
VehicleManager
{

public:
    ~VehicleManager(){}
    VehicleManager(const VehicleManager&)=delete;
    VehicleManager& operator=(const VehicleManager&)=delete;
    static VehicleManager& getInstance()
    {
        static VehicleManager instance;
        return instance;
    }

private:
    VehicleManager()
    {

    }

// 私有成员变量定义
private:
    AMap<AString, Vehicle::VehiclePtr> mVehicles;    ///> 车辆列表，用于管理全部车辆

};
} // namespace vehicleawesome
