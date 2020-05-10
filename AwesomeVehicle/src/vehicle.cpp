#include "vehicle.hpp"


namespace awesomevehicle
{
Vehicle::Vehicle(const AString &name) : mSelfName(name)
{

}


Vehicle::~Vehicle()
{

}


/**
 * brief: 读取速度值，单位 km/h
 **/
double Vehicle::velocity(const double &vel)
{

}
/**
 * brief: 设置速度值，单位 km/h
 **/
bool Vehicle::setVelocity(const double &vel)
{

}

/**
 * brief: 读取轮偏角，单位 弧度
 **/
double Vehicle::steeringAngle()
{

}
/**
 * brief: 设置轮偏角，单位 弧度
 **/
bool Vehicle::setSteeringAngle(const double &angle)
{

}


/**
 * brief: 设置驾驶模式
 **/
bool Vehicle::setDriveMode(const DriveModel &model)
{

}



} // namespace awesomevehicle



