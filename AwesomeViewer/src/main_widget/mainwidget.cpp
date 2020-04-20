#include "mainwidget.h"
#include "rvizview/rvizview.h"

namespace mainwidget {

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(new RvizView(this));

    // 通过tablewidget来分组管理控件
    QTabWidget *tabWidget = new QTabWidget(this);
    layout->addWidget(tabWidget);
    tabWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    tabWidget->setTabPosition(QTabWidget::South);
    tabWidget->addTab(new QWidget(this), "车辆控制");
    tabWidget->addTab(new DataRecWidget(this), "数据采集");

}

MainWidget::~MainWidget()
{

}

}