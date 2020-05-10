#include <iostream>

#include <yaml-cpp/yaml.h>

#include "awesome_vehicle.hpp"
#include "vehicle.hpp"
#include "vehicle_manager.hpp"
#include "vehicle_factory.hpp"

int main(int argc, char *argv[])
{
	char ch;
    std::cout << "Vehicle Runing..." << std::endl;
    
    YAML::Node root = YAML::Load("[]");
    YAML::Node item = YAML::Load("{}");

    item["name"] = "博瑞";
    item["tag"] = "borui";
    item["type"] = "Car";
    item["params"] = YAML::Load("{}");
    root.push_back(item);

    // 判断根节点是否存在
    if(!root.IsDefined())
    {
        goto exit;
    }
    // 判断根节点是否符合要求：必须为列表
    if(!root.IsSequence())
    {
        goto exit;
    }

    for(auto itor = root.begin(); itor != root.end(); itor++)
    {
        awe::Vehicle::VehicleUniquePtr vehicle;
        awe::VehicleFactory vf; 
        vf.produceVehicle((*itor)["tag"].as<std::string>(), "", vehicle);
        awe::VehicleManager::getInstance().add("", vehicle);
    }

try {


    // 启动所有车辆
    awe::VehicleManager::getInstance().runAll();

    // 进入事件循环
    awe::spin();

    // 关闭所有车辆
    awe::VehicleManager::getInstance().stopAll();

}catch(awe::AException &e)
{
    std::cout << e.what() << std::endl;
}

exit:
    std::cout << "Vehicle Exist!!!" << std::endl;
    return 0;
}