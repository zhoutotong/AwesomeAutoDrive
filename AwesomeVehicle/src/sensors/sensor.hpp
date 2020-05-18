#pragma once

#include <iostream>
#include <memory>
#include <utility>

#include "base_device.hpp"
#include "typedef.hpp"

namespace awe
{

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

    Sensor(const AString &name, const AString &tag, const AString &id, const AString &type) : 
    BaseDevice(name, tag, id, type)
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
