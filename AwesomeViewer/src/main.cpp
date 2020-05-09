#include "mainwindow.h"
#include <ros/ros.h>
#include <QApplication>
#include "utilities/execctl.h"
#include "utilities/rostools.h"

int main(int argc, char *argv[])
{
    // 初始化 ROS 部分
    utilities::RosTools::get_instance().initRosTools(argc, argv);

    // 注册并启动监测线程
    execctl::ExecCtl::get_instance().startAll();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
