#include "sensor_factory.hpp"
#include "daheng/daheng.hpp"
#include "simple_cam/simple_vcam.hpp"
#include "utilities/cfgchecker.hpp"


namespace awe
{

SensorFactory::SensorFactory() : 
BaseFactory("","","","")
{
    SensorListPtr cams(new SensorList);
    cams->insert(REGISTER_SENSOR("DaHeng", DaHeng));
    cams->insert(REGISTER_SENSOR("SimpleVCam", SimpleVCam));
    mSensors.insert(std::make_pair(AString("Camera"), cams));
}

BaseDevice::BaseDeviceUniquePtr SensorFactory::produce(const YAML::Node &node) const
{
    CfgChecker::nodeIsOk(node);
    auto type = mSensors.find(node["type"].as<AString>());
    if(type != mSensors.end())
    {
        auto sensors = type->second;
        auto sensorMaker = sensors->find(node["tag"].as<AString>());
        if(sensorMaker != sensors->end())
        {
            // const AString &name, const AString &tag, const AString &label, const AString &type
            return (sensorMaker->second)(node["name"].as<AString>(), 
            node["tag"].as<AString>(), 
            node["label"].as<AString>(), 
            node["type"].as<AString>());
        }
        else
        {
            throw AException("Sensor Device " + node["tag"].as<AString>() + " Is Not Exist.");
        }
        
    }
    else
    {
        throw AException("Sensor Type " + node["type"].as<AString>() + " Is Not Exist.");
    }
    
}

} // namespace awe
