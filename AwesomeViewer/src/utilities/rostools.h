#ifndef _ROS_TOOLS_H_
#define _ROS_TOOLS_H_

#include <iostream>
#include <vector>
#include <list>
#include <map>

#include <ros/ros.h>
#include <ros/topic.h>

namespace utilities
{
class RosTools
{
public:
    static std::map<std::string, std::string> getTopicList();
};    
}



#endif // _ROS_TOOLS_H_