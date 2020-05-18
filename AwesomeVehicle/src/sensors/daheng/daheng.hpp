#pragma once

#include "camera.hpp"

namespace awe
{

class DaHeng : public Camera
{

public:
    DaHeng(const AString &name, const AString &tag, const AString &id, const AString &type);
    ~DaHeng();

    virtual void setup() override;   // 初始化
    virtual void release() override; // 销毁
    virtual void start() override;   // 启动
    virtual void stop() override;    // 停止

};

}