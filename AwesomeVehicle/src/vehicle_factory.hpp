#pragma once

#include <iostream>

// yaml 头文件
#include <yaml-cpp/yaml.h>

#include "utilities/typedef.hpp"
#include "utilities/cfgchecker.hpp"
#include "vehicle.hpp"
#include "vehicle_manager.hpp"
#include "sensors/sensor_factory.hpp"

#include "awe.hpp"

namespace awe
{
template<typename T>
class VehicleFactory
{

protected:
    using _DevPtr = std::shared_ptr<T>;
    using _DevConstPtr = std::shared_ptr<const T>;
    using _DevUniquePtr = std::unique_ptr<T>;

public:
    using DevPtr = typename VehicleFactory::_DevPtr;
    using DevConstPtr = typename VehicleFactory::_DevConstPtr;
    using DevUniquePtr = typename VehicleFactory::_DevUniquePtr;


public:
    explicit VehicleFactory(){
        // 与主机厂有合作的各种厂家
        mFactorys.insert({"sensors", SensorFactory::instance()});
    };
    ~VehicleFactory(){};

    void produceVehicle(const YAML::Node &root, DevPtr &vehicle)
    {
        AWE_INFO << root << std::endl;

        // 检查配置文件是否合法，如不合法将会抛出异常
        CfgChecker::nodeIsOk(root);
        // 加载车辆信息，此时完成一辆空车的生产
        vehicle = std::make_shared<T>(root["name"].as<AString>(),
                                            root["tag"].as<AString>(),
                                            root["id"].as<AString>(),
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
                            BaseDevice::BaseDevicePtr dev = factory->second.produce(*d);
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

private:

    AMap<const AString, const BaseFactory&> mFactorys;


};
} // namespace awe
