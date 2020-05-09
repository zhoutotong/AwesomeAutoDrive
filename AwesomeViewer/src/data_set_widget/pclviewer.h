#ifndef PCLVIEWER_H
#define PCLVIEWER_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QListWidget>
#include <QSplitter>
#include <QFileDialog>
#include <QUrl>
#include <QListWidgetItem>
#include <QLabel>


#include <pcl/features/normal_3d.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/console/parse.h>
#include <pcl/PCLPointCloud2.h>

#include <QVTKWidget.h>
#include <vtkRenderWindow.h>

// #include "pcl/visualization/pcl_visualizer.h"

class FileListWidgetItem : public QListWidgetItem
{
public:
    explicit FileListWidgetItem(const QFileInfo &fileInfo, QListWidget *parent = nullptr)
    : QListWidgetItem(fileInfo.fileName(), parent)
    , info(fileInfo){}

    ~FileListWidgetItem(){}
    inline QFileInfo getFileInfo() { return info; }
private:
    const QFileInfo info;
};


class PCLViewer : public QWidget
{
    Q_OBJECT
public:
    explicit PCLViewer(QWidget *parent = nullptr);

public:

private:
    QString mCurrentDir;
    QListWidget *mFileList;
    QVTKWidget *mVtkWidget;
    pcl::visualization::PCLVisualizer::Ptr mViewer;

    QTextEdit *mCommentEdit;

    QLabel *mFileTitle;

public slots:
    void openDir();
    void changePCLFile(QListWidgetItem *current, QListWidgetItem *previous);
    void checkPass();
    void checkError();

signals:

};

#endif // PCLVIEWER_H
