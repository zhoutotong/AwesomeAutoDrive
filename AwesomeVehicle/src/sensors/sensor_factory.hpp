#pragma once

#include <iostream>
#include "base_factory.hpp"
#include "sensor.hpp"

namespace awe
{
class SensorFactory : public BaseFactory
{
protected:
    typedef BaseDevice::BaseDevicePtr(*_SensorCreator)(const AString &name, const AString &tag, const AString &id, const AString &type);

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

    BaseDevice::BaseDevicePtr produce(const YAML::Node &node) const override;

private:
    explicit SensorFactory();

private:
    SensorTypeList mSensors;

#define REGISTER_SENSOR(tag, obj) \
        std::make_pair<AString, SensorCreator>(\
        AString(tag), \
        [](const AString &_name, const AString &_tag, const AString &_id, const AString &_type)->\
        BaseDevice::BaseDevicePtr{return std::make_shared<obj>(_name, _tag, _id, _type);})
};
} // namespace awe
