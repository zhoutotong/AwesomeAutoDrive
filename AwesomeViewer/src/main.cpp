#include "mainwindow.h"
#include <ros/ros.h>
#include <QApplication>
#include "utilities/execctl.h"
#include "utilities/rostools.h"
#include "utilities/utilities.h"

#include "rvizview/visualizer_app.h"
#include <unistd.h>

int main(int argc, char *argv[])
{

    utilities::APathHelper::init(argv[0]);

    // 初始化 ROS 部分
    // utilities::RosTools::get_instance().initRosTools(argc, argv);

    // 注册并启动监测线程
    execctl::ExecCtl::get_instance().startAll();

    QApplication a(argc, argv);
    rviz::VisualizerApp vapp;
    vapp.setApp( &a );
    if(!vapp.init(argc, argv))
    {
        return 1;
    }
    MainWindow w(&vapp);

    w.show();
    return a.exec();

}
