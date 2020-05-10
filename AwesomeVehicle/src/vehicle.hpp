#pragma once

#include <iostream>
#include <memory>

#include "utilities/typedef.hpp"
// #include "chassis.h"


namespace awesomevehicle
{


typedef enum _DriveMode{
    Normal = 0,
    Auto = 1,
    Remote = 2,
} DriveMode;

class Vehicle
{

protected:
    using Ptr = std::shared_ptr<Vehicle>;
    using ConstPtr = std::shared_ptr<const Vehicle>;

public:
    using VehiclePtr = typename Vehicle::Ptr;
    using VehicleConstPtr = typename Vehicle::ConstPtr;

public:
    explicit Vehicle(const AString &name);
    ~Vehicle();

public:
    /**
     * brief: 读取速度值，单位 km/h
     **/
    double velocity(const double &vel);
    /**
     * brief: 设置速度值，单位 km/h
     **/
    bool setVelocity(const double &vel);

    /**
     * brief: 读取轮偏角，单位 弧度
     **/
    double steeringAngle();
    /**
     * brief: 设置轮偏角，单位 弧度
     **/
    bool setSteeringAngle(const double &angle);


    /**
     * brief: 设置驾驶模式
     **/
    bool setDriveMode(const DriveMode &model);
    /**
     * brief: 读取驾驶模式
     **/
    inline DriveMode driveMode() const { return mDriveMode; };

private:
    const AString mSelfName; ///> 车辆名称
    DriveMode mDriveMode;

};
} // namespace awesomevehicle


