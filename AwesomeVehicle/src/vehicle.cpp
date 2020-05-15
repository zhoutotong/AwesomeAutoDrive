#include "vehicle.hpp"
#include "sensors/sensor_factory.hpp"

namespace awe
{
Vehicle::Vehicle(const AString &name, const AString &tag, const AString &label, const AString &type) : 
    mName(name)
  , mTag(tag)
  , mLabel(label)
  , mType(type)
{
}


Vehicle::~Vehicle()
{

}

/**
 * brief: 初始化车辆
 **/
void Vehicle::setup()
{
    // 初始化传感器
    for(auto itor = mDevices.begin(); itor != mDevices.end(); itor++)
    {
        itor->second->setup();
    }
    return;
}
/**
 * brief: 释放资源
 **/
void Vehicle::release()
{
    // 释放传感器资源
    for(auto itor = mDevices.begin(); itor != mDevices.end(); itor++)
    {
        itor->second->release();
    }


    // 释放全部相关资源
    mDevices.clear();// 释放全部传感器资源
    return;
}

/**
 * brief: 启动车辆
 **/
void Vehicle::start()
{
    // 启动传感器
    for(auto itor = mDevices.begin(); itor != mDevices.end(); itor++)
    {
        itor->second->start();
    }
    return;
}

/**
 * brief: 停止运行
 **/
void Vehicle::stop()
{
    // 停止传感器
    for(auto itor = mDevices.begin(); itor != mDevices.end(); itor++)
    {
        itor->second->start();
    }
    return;
}


/**
 * brief: 读取速度值，单位 km/h
 **/
double Vehicle::velocity(const double &vel)
{

}
/**
 * brief: 设置速度值，单位 km/h
 **/
bool Vehicle::setVelocity(const double &vel)
{

}

/**
 * brief: 读取轮偏角，单位 弧度
 **/
double Vehicle::steeringAngle()
{

}
/**
 * brief: 设置轮偏角，单位 弧度
 **/
void Vehicle::setSteeringAngle(const double &angle)
{

}


/**
 * brief: 设置驾驶模式
 **/
void Vehicle::setDriveMode(const DriveMode &model)
{

}

void Vehicle::plugDevice(BaseDevice::BaseDeviceUniquePtr &dev)
{
    // 查找是否存在重名的
    auto itor = mDevices.find(dev->getLabel());
    if(itor != mDevices.end())
    {
        throw AException("Plug Device " + dev->getLabel() + " To Vehicle Failed: Same Tag In Sensors.");
    }
    mDevices.insert(
        std::make_pair<AString, BaseDevice::BaseDeviceUniquePtr>(
            dev->getLabel(), std::move(dev)
        ));
}

} // namespace awe



