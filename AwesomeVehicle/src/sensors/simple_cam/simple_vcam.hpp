#pragma once
#include <iostream>
#include "camera.hpp"

namespace awe
{
class SimpleVCam : public Camera
{
public:
    SimpleVCam(const AString &name, const AString &tag, const AString &id, const AString &type);
    ~SimpleVCam();

    virtual void setup() override;   // 初始化
    virtual void release() override; // 销毁
    virtual void start() override;   // 启动
    virtual void stop() override;    // 停止
};
} // namespace awe
