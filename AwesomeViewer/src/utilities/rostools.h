#ifndef _ROS_TOOLS_H_
#define _ROS_TOOLS_H_

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <fstream>
#include <functional>
#include <thread>

#include <ros/ros.h>
#include <ros/topic.h>

#include <QString>
#include <QRegExp>
#include <QStringList>

#include <yaml-cpp/yaml.h>

#include "cfgfilehelper.h"

#include "nox_msgs/Chassis.h"
#include "nox_msgs/DrivingCommand.h"

namespace utilities
{
class RosTools
{
public:

    ~RosTools(){

        __isWorking = false;
        if(__workThread)
        {
            __workThread->join();
            delete __workThread;
            __workThread = nullptr;
        }

        if(__n)
        {
            delete __n;
            __n = nullptr;
        }
    }
    RosTools(const RosTools &) = delete;
    RosTools &operator = (const RosTools&) = delete;
    static RosTools & get_instance() {
        static RosTools instance;
        return instance;
    }

    void initRosTools(int argc, char *argv[]);
    void subscribeTopics();

    double getSpeed();
    double getSteering();
    double getCtlSpeed();
    double getCtlSteering();

    // static functions
    static std::map<std::string, std::string> getTopicList();
    static void generateTopicWatch(const std::string &node_name, const std::string &node, const std::string &output);
    

private:
    RosTools();

    ros::NodeHandle *__n;
    std::thread *__workThread;
    bool __isWorking;

private:
    void chassisCb(const nox_msgs::Chassis::ConstPtr &msg);
    void drivingCommandCb(const nox_msgs::DrivingCommand::ConstPtr &msg);
};
}



#endif // _ROS_TOOLS_H_
