#include "vehicle_factory.hpp"

namespace awe
{
VehicleFactory::VehicleFactory()
{

}

VehicleFactory::~VehicleFactory()
{

}

void VehicleFactory::produceVehicle(const AString &name, const AString &cfgFile, Vehicle::VehicleUniquePtr &vehicle)
{
    YAML::Node n;

    const AString vn = "Car";
    n = YAML::Load("[]");
    YAML::Node item;
    item["name"] = "mid_cam";
    item["type"] = "CAMERA";
    item["model"] = "daheng";
    item["label"] = "主视相机";
    item["params"] = "~/.config/cam.yaml";

    YAML::Node veh;
    veh["name"] = "Car";
    veh["label"] = "测试车辆";
    veh["params"] = "~/.config/vehicle.yaml";
    veh["sensors"].push_back(item);

    n.push_back(veh);

    // Sensor::SensorUniquePtr sensor = std::make_unique<Sensor>();
    // vehicle->plugSensor("Cam", sensor);


    std::cout << n << std::endl;

}

} // namespace awe
