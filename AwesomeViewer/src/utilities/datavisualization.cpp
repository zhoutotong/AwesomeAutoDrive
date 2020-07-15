#include "datavisualization.hpp"

namespace utilities
{
DataVisualization::DataVisualization()
{
    // speedPub = ros::Publisher<awe_visualization::DoubleValueMeterParam>();
    
    ros::NodeHandle _n("~");
    
    subChassis = _n.subscribe<nox_msgs::Chassis>("/chassis", 10, std::bind(&DataVisualization::chassisWatchCallback, this, std::placeholders::_1));
    subControl = _n.subscribe<nox_msgs::DrivingCommand>("/driving_command", 10, std::bind(&DataVisualization::controlWatchCallback, this, std::placeholders::_1));

    speedPub = _n.advertise<awe_visualization::DoubleValueMeterParam>("/speed_meter", 10);
    steerPub = _n.advertise<awe_visualization::DoubleValueMeterParam>("/steer_meter", 10);

    speedParam.label = "speed";
    steerParam.label = "steering";
    speedParam.max = 60;
    speedParam.min = 0;
    steerParam.max = 720;
    steerParam.min = -720;
}
DataVisualization::~DataVisualization()
{

}

void DataVisualization::chassisWatchCallback(const nox_msgs::ChassisConstPtr &msg)
{
    speedParam.val_b = msg->speed;
    steerParam.val_b = msg->steering;
    speedPub.publish(speedParam);
    steerPub.publish(steerParam);
}

void DataVisualization::controlWatchCallback(const nox_msgs::DrivingCommandConstPtr &msg)
{
    speedParam.val_a = msg->target_speed;
    steerParam.val_a = msg->target_steering;
    speedPub.publish(speedParam);
    steerPub.publish(steerParam);
}


}