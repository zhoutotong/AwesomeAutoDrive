#pragma once

#include <iostream>

#include "sensor.hpp"

namespace awe
{

class Camera : public Sensor
{
public:
    Camera(const AString &name, const AString &tag, const AString &label, const AString &type);
    ~Camera();

    virtual void setup() = 0;    // 初始化
    virtual void release() = 0;  // 销毁
    virtual void start() = 0;    // 启动
    virtual void stop() = 0;     // 停止

};


} // namespace awe
