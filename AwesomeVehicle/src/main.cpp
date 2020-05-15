#include <iostream>

#include <yaml-cpp/yaml.h>

#include "awesome_vehicle.hpp"
#include "vehicle.hpp"
#include "vehicle_manager.hpp"
#include "vehicle_factory.hpp"
#include "awe.hpp"

int main(int argc, char *argv[])
{
    char ch;
    awe::AWE_INFO << "Awesome Vehicle" << std::endl;

    YAML::Node root = YAML::Load("[]");
    YAML::Node vehicleNode = YAML::Load("{}");

    vehicleNode["name"] = "博瑞";
    vehicleNode["label"] = "qingdao_borui";
    vehicleNode["tag"] = "borui";
    vehicleNode["type"] = "Car";
    vehicleNode["params"] = YAML::Load("{}");
    root.push_back(vehicleNode);

    YAML::Node sensorNode = YAML::Load("{}");
    sensorNode["name"] = "大恒相机";
    sensorNode["label"] = "front_cam";
    sensorNode["tag"] = "DaHeng";
    sensorNode["type"] = "Camera";
    sensorNode["params"] = YAML::Load("{}");

    vehicleNode["params"]["sensors"].push_back(sensorNode);

    awe::AWE_INFO << root << std::endl;

    // 判断根节点是否存在
    if (!root.IsDefined())
    {
        goto exit;
    }
    // 判断根节点是否符合要求：必须为列表
    if (!root.IsSequence())
    {
        goto exit;
    }

    for (auto itor = root.begin(); itor != root.end(); itor++)
    {
        awe::Vehicle::VehicleUniquePtr vehicle;
        awe::VehicleFactory vf;
        vf.produceVehicle(*itor, vehicle);
        awe::VehicleManager::getInstance().add("", vehicle);
    }

    try
    {
        // 启动所有车辆
        awe::VehicleManager::getInstance().runAll();

        // 进入事件循环
        awe::spin();

        // 关闭所有车辆
        awe::VehicleManager::getInstance().stopAll();
    }
    catch (awe::AException &e)
    {
        std::cout << e.what() << std::endl;
    }

exit:
    awe::AWE_INFO << "Vehicle Exist!!!" << std::endl;
    return 0;
}