#include "dataviewer.h"
#include "pclviewer.h"

DataViewer::DataViewer(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    PCLViewer *pclViewer = new PCLViewer(this);


    layout->addWidget(pclViewer);
}
