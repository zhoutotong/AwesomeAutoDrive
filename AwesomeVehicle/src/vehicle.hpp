#pragma once

#include <iostream>
#include <memory>

#include "utilities/typedef.hpp"
#include "utilities/aexception.hpp"
#include "sensors/sensor.hpp"
#include "base_factory.hpp"
#include "base_device.hpp"

namespace awe
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
    using UniquePtr = std::unique_ptr<Vehicle>;

public:
    using VehiclePtr = typename Vehicle::Ptr;
    using VehicleConstPtr = typename Vehicle::ConstPtr;
    using VehicleUniquePtr = typename Vehicle::UniquePtr;

public:
    Vehicle() = delete;
    Vehicle(const AString &name, const AString &tag, const AString &label, const AString &type);
    ~Vehicle();

    /**
     * brief: 初始化车辆
     **/
    void setup();
    /**
     * brief: 释放资源
     **/
    void release();

    /**
     * brief: 启动车辆
     **/
    void start();

    /**
     * brief: 停止运行
     **/
    void stop();


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
    void setSteeringAngle(const double &angle);


    /**
     * brief: 设置驾驶模式
     **/
    void setDriveMode(const DriveMode &model);
    /**
     * brief: 读取驾驶模式
     **/
    inline DriveMode driveMode() const { return mDriveMode; };

// 装配接口
public:
    void plugDevice(BaseDevice::BaseDeviceUniquePtr &dev);

private:
    const AString mName;  ///> 车辆名称
    const AString mTag;   ///> 标签
    const AString mLabel; ///> 识别标签
    const AString mType;  ///> 类别
    DriveMode mDriveMode;

    AMap<const AString, const BaseDevice::BaseDeviceUniquePtr> mDevices;

};
} // namespace awe


