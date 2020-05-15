#pragma once

#include <iostream>
#include <memory>
#include <utility>

#include "base_device.hpp"
#include "typedef.hpp"

namespace awe
{


typedef enum _SensorType
{
    SENSOR_TYPE_UNDEF = 0,
    SENSOR_TYPE_CAMERA = 1,
} SensorType;

class Sensor : public BaseDevice
{

protected:
    using Ptr = std::shared_ptr<Sensor>;
    using ConstPtr = std::shared_ptr<const Sensor>;
    using UniquePtr = std::unique_ptr<Sensor>;
public:
    using SensorPtr = typename Sensor::Ptr;
    using SensorConstPtr = typename Sensor::ConstPtr;
    using SensorUniquePtr = typename Sensor::UniquePtr;

public:

    Sensor(const AString &name, const AString &tag, const AString &label, const AString &type) : 
    BaseDevice(name, tag, label, type)
    {
    }

    ~Sensor(){}

    // 传感器控制接口
    virtual void setup();    // 初始化
    virtual void release();  // 销毁
    virtual void start();    // 启动
    virtual void stop();     // 停止

private:
};


} // namespace awe
