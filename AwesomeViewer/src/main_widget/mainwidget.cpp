#include "mainwidget.h"
#include "rvizview/rvizview.h"
#include "pathplayer.hpp"
#include "vehiclecontrol.hpp"

namespace mainwidget {

MainWidget::MainWidget(const rviz::VisualizerApp *vapp, QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QSplitter *splitter = new QSplitter(Qt::Vertical, this);
    layout->addWidget(splitter);

    // 通过tablewidget来分组管理控件
    QTabWidget *tabWidget = new QTabWidget(this);
    tabWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    tabWidget->setTabPosition(QTabWidget::South);
    // tabWidget->addTab(new VehicleControl(this), "车辆控制");
    tabWidget->addTab(new DataRecWidget(this), "数据采集");
    tabWidget->addTab(new PathPlayer(this), "路径规划");

    splitter->addWidget(vapp->getFrame());
    splitter->addWidget(tabWidget);

}

MainWidget::~MainWidget()
{

}

}