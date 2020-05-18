#pragma once
#include <iostream>
#include <memory>
#include <utility>


#include "awe.hpp"


namespace awe
{
class BaseDevice
{

protected:
    using Ptr = std::shared_ptr<BaseDevice>;
    using ConstPtr = std::shared_ptr<const BaseDevice>;
    using UniquePtr = std::unique_ptr<BaseDevice>;
public:
    using BaseDevicePtr = typename BaseDevice::Ptr;
    using BaseDeviceConstPtr = typename BaseDevice::ConstPtr;
    using BaseDeviceUniquePtr = typename BaseDevice::UniquePtr;

public:
    BaseDevice(const BaseDevice &) = delete;
    BaseDevice(const AString &name, const AString &tag, const AString &id, const AString &type);
    ~BaseDevice();

    virtual void setup();    // 初始化
    virtual void release();  // 销毁
    virtual void start();    // 启动
    virtual void stop();     // 停止

    inline AString getName() { return mName; }
    inline AString getTag()  { return mTag; }
    inline AString getId() { return mId; }
    inline AString getType() { return mType; }
private:
    const AString mName;  ///> 车辆名称
    const AString mTag;   ///> 标签
    const AString mId; ///> 识别标签
    const AString mType;  ///> 类别

};
} // namespace awe
