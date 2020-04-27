#include "mainwindow.h"
#include <ros/ros.h>
#include <QApplication>
#include "utilities/execctl.h"

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "Awesome");
    ros::NodeHandle _n("~");

    // 注册并启动监测线程
    execctl::ExecCtl::get_instance().startAll();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
