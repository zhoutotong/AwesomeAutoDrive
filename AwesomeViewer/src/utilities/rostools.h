#ifndef _ROS_TOOLS_H_
#define _ROS_TOOLS_H_

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <fstream>

#include <ros/ros.h>
#include <ros/topic.h>

#include <QString>
#include <QRegExp>
#include <QStringList>

#include <yaml-cpp/yaml.h>

#include "cfgfilehelper.h"

namespace utilities
{
class RosTools
{
public:
    static std::map<std::string, std::string> getTopicList();
    static void generateTopicWatch();
};    
}



#endif // _ROS_TOOLS_H_