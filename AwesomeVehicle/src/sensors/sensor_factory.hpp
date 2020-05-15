#pragma once

#include <iostream>
#include "base_factory.hpp"
#include "sensor.hpp"

namespace awe
{
class SensorFactory : public BaseFactory
{
protected:
    typedef BaseDevice::BaseDeviceUniquePtr(*_SensorCreator)(const AString &name, const AString &tag, const AString &label, const AString &type);

public:

    using SensorCreator = _SensorCreator;

    using SensorList = AMap<AString, SensorCreator>;
    using SensorListPtr = std::shared_ptr<SensorList>;

    using SensorTypeList = AMap<AString, SensorListPtr>;

public:
    ~SensorFactory(){}
    SensorFactory(const SensorFactory&)=delete;
    SensorFactory& operator=(const SensorFactory&)=delete;
    static SensorFactory& instance(){
        static SensorFactory sf;
        return sf;
    }

    BaseDevice::BaseDeviceUniquePtr produce(const YAML::Node &node) const override;

private:
    explicit SensorFactory();

private:
    SensorTypeList mSensors;

#define REGISTER_SENSOR(tag, obj) \
        std::make_pair<AString, SensorCreator>(\
        AString(tag), \
        [](const AString &_name, const AString &_tag, const AString &_label, const AString &_type)->\
        BaseDevice::BaseDeviceUniquePtr{return std::make_unique<obj>(_name, _tag, _label, _type);})
};
} // namespace awe
