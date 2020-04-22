#include "rostools.h"

namespace utilities
{
std::map<std::string, std::string> RosTools::getTopicList()
{
    ros::master::V_TopicInfo topics;
    std::map<std::string, std::string> ts;
    ros::master::getTopics(topics);
    for(auto itor = topics.begin(); itor != topics.end(); itor++)
    {
        ts.insert(std::pair<std::string, std::string>(itor->name, itor->datatype));
    }
    return ts;
}
} // namespace utilities
