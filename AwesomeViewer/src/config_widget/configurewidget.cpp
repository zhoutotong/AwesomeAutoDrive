#include "configurewidget.h"
#include "modelconfigwidget.h"
#include "datareccfg.h"

ConfigureWidget::ConfigureWidget(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout *l = new QHBoxLayout(this);

    QTabWidget *tabWidget = new QTabWidget(this);
    l->addWidget(tabWidget);
    tabWidget->setTabPosition(QTabWidget::South);
    tabWidget->addTab(new ModelConfigWidget(this), "Modules");
    tabWidget->addTab(new DataRecCfg(this), "DataRec");

    tabWidget->setMovable(true);

    utilities::RosTools::generateTopicWatch();

//    mTableWidget = new QTableWidget(this);
//    l->addWidget(mTableWidget);

//    mTableWidget->setColumnCount(5);
//    mTableWidget->setRowCount(2);
//    mTableWidget->verticalHeader()->setVisible(false);

//    QTableWidgetItem *newItem = new QTableWidgetItem();

//    mTableWidget->setItem(1, 1, newItem);
//    mTableWidget->setCellWidget(1, 2, new QPushButton("Delete"));

}
