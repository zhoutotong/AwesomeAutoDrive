#pragma once

#include <iostream>

#include "vehicle.hpp"
#include "utilities/typedef.hpp"
#include "utilities/aexception.hpp"

namespace awe
{
class VehicleManager
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

    void add(const AString &id, const Vehicle::VehiclePtr &vehicle);
    void remove(const AString &id);

    void setupAll();
    void releaseAll();

    void runAll();
    void stopAll();
    void run(const AString &name);
    void stop(const AString &name);

    void exist();

private:
    VehicleManager()
    {

    }

// 私有成员变量定义
private:
    AMap<AString, Vehicle::VehiclePtr> mVehicles;    ///> 车辆列表，用于管理全部车辆

};
} // namespace awe
