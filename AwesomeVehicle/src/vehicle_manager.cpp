#include "vehicle_manager.hpp"


namespace awe
{

void VehicleManager::setupAll()
{
    for(auto itor = mVehicles.begin(); itor != mVehicles.end(); itor++)
    {
        itor->second->setup();
    }
}
void VehicleManager::releaseAll()
{
    for(auto itor = mVehicles.begin(); itor != mVehicles.end(); itor++)
    {
        itor->second->release();
    }
}
void VehicleManager::runAll()
{
    for(auto itor = mVehicles.begin(); itor != mVehicles.end(); itor++)
    {
        itor->second->start();
    }
}
void VehicleManager::stopAll()
{
    for(auto itor = mVehicles.begin(); itor != mVehicles.end(); itor++)
    {
        itor->second->stop();
    }
}
void VehicleManager::run(const AString &id)
{
    auto itor = mVehicles.find(id);
    if(itor != mVehicles.end())
    {
        itor->second->start();
    }
}
void VehicleManager::stop(const AString &id)
{
    auto itor = mVehicles.find(id);
    if(itor != mVehicles.end())
    {
        itor->second->stop();
    }
}

void VehicleManager::add(const AString &id, const Vehicle::VehiclePtr &vehicle)
{
    // 查找是否存在重名的
    auto itor = mVehicles.find(id);
    if(itor != mVehicles.end())
    {
        throw AException("Add Vehicle To Manager Failed: Same Tag In Vehicles.");
    }

    mVehicles[id] = vehicle;
}
void VehicleManager::remove(const AString &id)
{
    auto itor = mVehicles.find(id);
    if(itor != mVehicles.end())
    {
        mVehicles.erase(itor->first);
    }
}

void VehicleManager::exist()
{
    mVehicles.clear();
}

} // namespace awe