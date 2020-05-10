#pragma once

#include <iostream>
#include <memory>

#include "typedef.hpp"

namespace awe
{

typedef enum _SensorType
{
    SENSOR_TYPE_UNDEF = 0,
    SENSOR_TYPE_CAMERA = 1,
} SensorType;

class Sensor
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

    explicit Sensor(const SensorType &type = SENSOR_TYPE_UNDEF) : mType(type)
    , mName("")
    {

    }

    ~Sensor(){}

    // 传感器控制接口
    virtual void setup() = 0;    // 初始化
    virtual void release() = 0;  // 销毁
    virtual void start() = 0;    // 启动
    virtual void stop() = 0;     // 停止


    // 读取传感器类型
    inline const SensorType &getType() const { return mType; }

    // 读取传感器名称
    inline const AString &getName() const { return mName; }
    // 设置传感器名称
    inline void setName(AString n) { mName = n; }


private:
    const SensorType mType;
    AString mName;

};


} // namespace awe
