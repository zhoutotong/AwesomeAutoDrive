#pragma once

#include <iostream>

#include "utilities/typedef.hpp"

namespace awesomevehicle
{

typedef enum _SensorType
{
    SENSOR_TYPE_UNDEF = 0,
    SENSOR_TYPE_CAMERA = 1,
} SensorType;

class Sensor
{
public:
    explicit Sensor(const SensorType &type = SENSOR_TYPE_UNDEF) : mType(type)
    , mName("")
    {

    }

    ~Sensor(){}

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


} // namespace awesomevehicle
