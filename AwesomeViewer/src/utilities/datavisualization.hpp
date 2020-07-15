#pragma once

#include <ros/ros.h>
#include <QWidget>
#include "awe_visualization/DoubleValueMeterParam.h"
#include "nox_msgs/Chassis.h"
#include "nox_msgs/DrivingCommand.h"

namespace utilities
{
class DataVisualization
{
public:
    ~DataVisualization();
    DataVisualization(const DataVisualization&) = delete;
    DataVisualization& operator=(const DataVisualization&) = delete;
    static DataVisualization& get_instance(){
        static DataVisualization instance;
        return instance;
    }

private:
    DataVisualization();

    void chassisWatchCallback(const nox_msgs::ChassisConstPtr &msg);
    void controlWatchCallback(const nox_msgs::DrivingCommandConstPtr &msg);


private:
    ros::Publisher speedPub;
    ros::Publisher steerPub;

    ros::Subscriber subChassis;
    ros::Subscriber subControl;

    awe_visualization::DoubleValueMeterParam speedParam;
    awe_visualization::DoubleValueMeterParam steerParam;


};

}// mainwidget