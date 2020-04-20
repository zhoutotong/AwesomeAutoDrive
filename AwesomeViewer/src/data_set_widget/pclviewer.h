#ifndef PCLVIEWER_H
#define PCLVIEWER_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <pcl/features/normal_3d.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/console/parse.h>
#include <pcl/PCLPointCloud2.h>

#include <QVTKWidget.h>
#include <vtkRenderWindow.h>

// #include "pcl/visualization/pcl_visualizer.h"

class PCLViewer : public QWidget
{
    Q_OBJECT
public:
    explicit PCLViewer(QWidget *parent = nullptr);

public:

signals:

};

#endif // PCLVIEWER_H
