#include "datasetwidget.h"
#include "bag2datawidget.h"
#include "dataviewer.h"

DataSetWidget::DataSetWidget(QWidget *parent) : QWidget(parent)
{
    QTabWidget *tabWidget = new QTabWidget(this);
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(tabWidget);
    tabWidget->setTabPosition(QTabWidget::South);
    tabWidget->addTab(new Bag2DataWidget(this), "Bag2Data");
    tabWidget->addTab(new DataViewer(this), "DataViewer");
}
