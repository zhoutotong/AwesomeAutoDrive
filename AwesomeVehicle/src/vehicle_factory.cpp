#include "vehicle_factory.hpp"
#include "utilities/cfgchecker.hpp"
#include "sensors/sensor_factory.hpp"

namespace awe
{
VehicleFactory::VehicleFactory()
{
    // 与主机厂有合作的各种厂家
    mFactorys.insert({"sensors", SensorFactory::instance()});

}

VehicleFactory::~VehicleFactory()
{

}

void VehicleFactory::produceVehicle(const AString &name, const AString &cfgFile, Vehicle::VehicleUniquePtr &vehicle)
{
    // Sensor::SensorUniquePtr sensor = std::make_unique<Sensor>();
    // vehicle->plugSensor("Cam", sensor);
}

void VehicleFactory::produceVehicle(const YAML::Node &root, Vehicle::VehicleUniquePtr &vehicle)
{
    AWE_INFO << root << std::endl;

    // 检查配置文件是否合法，如不合法将会抛出异常
    CfgChecker::nodeIsOk(root);
    // 加载车辆信息，此时完成一辆空车的生产
    vehicle = std::make_unique<Vehicle>(root["name"].as<AString>(),
                                        root["tag"].as<AString>(),
                                        root["label"].as<AString>(),
                                        root["type"].as<AString>());

    // 接入设备
    YAML::Node factorys = root["params"];
    // 检查已经定义，并且是一个列表
    if(factorys.IsDefined() && factorys.IsMap())
    {
        // 开始逐个设备进行创建
        for(auto itor = factorys.begin(); itor != factorys.end(); itor++)
        {
            AString facName = itor->first.as<AString>();
            auto factory = mFactorys.find(facName);
            // 如果有这个工厂就使用这个工厂开始生产
            if(factory != mFactorys.end())
            {
                YAML::Node devs = factorys[facName];
                CfgChecker::nodeIsDefAndSequence(devs);
                for(auto d = devs.begin(); d != devs.end(); d++)
                {
                    // 开始创建设备，并接入车辆
                    try {
                        BaseDevice::BaseDeviceUniquePtr dev = factory->second.produce(*d);
                        vehicle->plugDevice(dev);
                    } catch (AException &e)
                    {
                        AWE_WARN << e.what() << std::endl;
                    }
                }
            }
            else
            {
                AWE_ERROR << "Factory: " << facName << " is Not Exist!!!" << std::endl;
            }
        }
    }
}

} // namespace awe
