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
} DriveModel;

class Vehicle
{

protected:
    using Ptr = std::shared_ptr<Vehicle>;
    using ConstPtr = std::shared_ptr<const Vehicle>;

public:
    using VehiclePtr = typename Vehicle::Ptr;
    using VehicleConstPtr = typename Vehicle::ConstPtr;

public:
    Vehicle() = delete;
    Vehicle(const AString &name, const AString &tag, const AString &id, const AString &type);
    ~Vehicle();

    /**
     * brief: 初始化车辆
     **/
    virtual void setup();
    /**
     * brief: 释放资源
     **/
    virtual void release();

    /**
     * brief: 启动车辆
     **/
    virtual void start();

    /**
     * brief: 停止运行
     **/
    virtual void stop();


public:
    /**
     * brief: 读取速度值，单位 km/h
     **/
    virtual double velocity(const double &vel);
    /**
     * brief: 设置速度值，单位 km/h
     **/
    virtual bool setVelocity(const double &vel);

    /**
     * brief: 读取轮偏角，单位 弧度
     **/
    virtual double steeringAngle();
    /**
     * brief: 设置轮偏角，单位 弧度
     **/
    virtual void setSteeringAngle(const double &angle);


    /**
     * brief: 设置驾驶模式
     **/
    void setDriveModel(const DriveModel &model);
    /**
     * brief: 读取驾驶模式
     **/
    inline DriveModel driveModel() const { return mDriveModel; };

// 装配接口
public:
    void plugDevice(const BaseDevice::BaseDevicePtr &dev);

private:
    const AString mName;  ///> 车辆名称
    const AString mTag;   ///> 标签
    const AString mId; ///> 识别标签
    const AString mType;  ///> 类别
    DriveModel mDriveModel;

    AMap<const AString, BaseDevice::BaseDevicePtr> mDevices;

};
} // namespace awe


