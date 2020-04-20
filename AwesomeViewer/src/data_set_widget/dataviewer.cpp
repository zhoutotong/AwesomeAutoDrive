#include "dataviewer.h"
#include "pclviewer.h"

DataViewer::DataViewer(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(new PCLViewer(this));
}
