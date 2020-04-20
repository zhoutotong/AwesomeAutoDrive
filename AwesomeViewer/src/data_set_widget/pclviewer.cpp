#include "pclviewer.h"


PCLViewer::PCLViewer(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    this->setLayout(layout);

    QVTKWidget *vtkWidget = new QVTKWidget(this);
    layout->addWidget(vtkWidget);


    pcl::PointCloud<pcl::PointXYZI>::Ptr basic_cloud_ptr(new pcl::PointCloud<pcl::PointXYZI>);
    pcl::io::loadPCDFile("/home/tong/Documents/bagparser/release/2020_04_14/drive_0000_extract/pointcloud_000/data/0000000000.pcd", 
        *(basic_cloud_ptr));
    
    pcl::visualization::PCLVisualizer::Ptr viewer;

    viewer.reset(new pcl::visualization::PCLVisualizer("3D Viewer", false));
    viewer->setBackgroundColor(0, 0, 0);
    pcl::visualization::PointCloudColorHandlerGenericField<pcl::PointXYZI>multi_color(basic_cloud_ptr, "intensity");
    viewer->removeAllPointClouds();
    viewer->addPointCloud<pcl::PointXYZI>(basic_cloud_ptr, multi_color, "sample cloud");
    viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "sample cloud");
    viewer->addCoordinateSystem(1.0);
    viewer->initCameraParameters();

    vtkWidget->SetRenderWindow(viewer->getRenderWindow());

}
