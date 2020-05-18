#pragma once

#include "awe.hpp"
#include "vehicle.hpp"

namespace awe
{
class BoRui : public Vehicle
{
public:
    BoRui(const AString &name, const AString &tag, const AString &id, const AString &type);
    ~BoRui();

    /**
     * brief: 初始化车辆
     **/
    virtual void setup();
    /**
     * brief: 释放资源
     **/
    virtual void release();

    /**
     * brief: 启动车辆
     **/
    virtual void start();

    /**
     * brief: 停止运行
     **/
    virtual void stop();


    /**
     * brief: 读取速度值，单位 km/h
     **/
    virtual double velocity(const double &vel){};
    /**
     * brief: 设置速度值，单位 km/h
     **/
    virtual bool setVelocity(const double &vel){};

    /**
     * brief: 读取轮偏角，单位 弧度
     **/
    virtual double steeringAngle(){};
    /**
     * brief: 设置轮偏角，单位 弧度
     **/
    virtual void setSteeringAngle(const double &angle){};
};
} // namespace awe
