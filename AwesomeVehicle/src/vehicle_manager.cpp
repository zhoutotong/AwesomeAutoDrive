#include "vehicle_manager.hpp"


namespace awe
{

void VehicleManager::runAll()
{

}
void VehicleManager::stopAll()
{

}
void VehicleManager::run(const AString &name)
{

}
void VehicleManager::stop(const AString &name)
{

}

void VehicleManager::add(const AString &tag, const Vehicle::VehicleUniquePtr &vehicle)
{
    // 查找是否存在重名的
    auto itor = mVehicles.find(tag);
    if(itor == mVehicles.end())
    {
        throw AException("Add Vehicle To Manager Failed: Same Tag In Vehicles.");
    }
    mVehicles.insert(std::make_pair<AString, Vehicle::VehicleUniquePtr>(tag.c_str(), std::make_unique<Vehicle>(std::move(vehicle))));
}
void VehicleManager::remove(const AString &tag)
{
    auto itor = mVehicles.find(tag);
    if(itor != mVehicles.end())
    {
        mVehicles.erase(itor->first);
    }
}


} // namespace awe