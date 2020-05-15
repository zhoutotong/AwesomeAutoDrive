#pragma once

#include <yaml-cpp/yaml.h>

#include "awe.hpp"
#include "base_device.hpp"


namespace awe
{

class BaseFactory
{
public:
    BaseFactory(const AString &name, const AString &tag, const AString &label, const AString &type);
    ~BaseFactory();

    void produce();

    virtual BaseDevice::BaseDeviceUniquePtr produce(const YAML::Node &node) const;

private:
    const AString mName;  ///> 名称
    const AString mTag;   ///> 标签
    const AString mLabel; ///> 识别标签
    const AString mType;  ///> 类别
};

} // namespace awe
