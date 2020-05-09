#pragma once

#include <iostream>

#include "utilities/typedef.hpp"
#include "chassis.h"


namespace awesomevehicle
{


typedef enum _DriveModel{
    Normal = 0,
    Auto = 1,
    Remote = 2,
} DriveModel;

class Vehicle
{

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

    bool setDriveModel(const DriveModel &model);
    DriveModel driveModel();

private:
    const AString mSelfName; ///> 车辆名称

};
} // namespace awesomevehicle


