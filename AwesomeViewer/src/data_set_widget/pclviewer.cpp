#include "pclviewer.h"
#include <QDebug>

PCLViewer::PCLViewer(QWidget *parent) : QWidget(parent)
  , mCurrentDir("./")
{
    QSplitter *splitter = new QSplitter(this);
    QSplitter *fileCommentSplitter = new QSplitter(Qt::Vertical, this);
    QWidget *leftWidget = new QWidget(this);
    leftWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QWidget *rightWidget = new QWidget(this);
    rightWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setMargin(0);
    this->setLayout(layout);
    layout->addWidget(splitter);
    splitter->addWidget(leftWidget);
    splitter->addWidget(rightWidget);

    QVBoxLayout *leftLayout = new QVBoxLayout(leftWidget);
    leftLayout->setMargin(0);
    QVBoxLayout *rightLayout = new QVBoxLayout(rightWidget);
    rightLayout->setMargin(0);

    mFileTitle = new QLabel(this);
    leftLayout->addWidget(mFileTitle);

    mVtkWidget = new QVTKWidget(this);
    leftLayout->addWidget(mVtkWidget);
    mVtkWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


    mViewer.reset(new pcl::visualization::PCLVisualizer("3D Viewer", false));

    mViewer->setBackgroundColor(0, 0, 0);
    mViewer->addCoordinateSystem(1.0);
    mViewer->initCameraParameters();

    mVtkWidget->SetRenderWindow(mViewer->getRenderWindow());



    QHBoxLayout *fileCtlLayout = new QHBoxLayout(rightWidget);
    QPushButton *openDirBtn = new QPushButton("打开目录");
    connect(openDirBtn, &QPushButton::clicked, this, &PCLViewer::openDir);
    fileCtlLayout->addWidget(openDirBtn);
    rightLayout->addLayout(fileCtlLayout);

    rightLayout->addWidget(fileCommentSplitter);
    mFileList = new QListWidget(this);

    connect(mFileList, &QListWidget::currentItemChanged, this, &PCLViewer::changePCLFile);

    mCommentEdit = new QTextEdit(this);
    rightLayout->addWidget(mCommentEdit);

    fileCommentSplitter->addWidget(mFileList);
    fileCommentSplitter->addWidget(mCommentEdit);

    QPushButton *errorBtn = new QPushButton("问题");
    QPushButton *passBtn = new QPushButton("通过");
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addWidget(errorBtn);
    btnLayout->addWidget(passBtn);
    rightLayout->addLayout(btnLayout);

    connect(errorBtn, &QPushButton::clicked, this, &PCLViewer::checkError);
    connect(passBtn, &QPushButton::clicked, this, &PCLViewer::checkPass);

}


void PCLViewer::openDir()
{
    const QStringList filters = {"*.pcd"};
    mCurrentDir = QFileDialog::getExistingDirectory(this, "打开", mCurrentDir,
                QFileDialog::ShowDirsOnly);

    QDir dir(mCurrentDir);
    QFileInfoList infoList = dir.entryInfoList(filters);

    mFileList->clear();

    for(auto info = infoList.begin(); info != infoList.end(); info++)
    {
        FileListWidgetItem *item = new FileListWidgetItem(*info, mFileList);
        item->setFlags(Qt::ItemIsEnabled);
    }
}


void PCLViewer::changePCLFile(QListWidgetItem *current, QListWidgetItem *previous)
{
    if(current == nullptr) return;
    FileListWidgetItem *item = static_cast<FileListWidgetItem*>(current);
    QFileInfo info = item->getFileInfo();

    mFileTitle->setText(info.filePath());

    pcl::PointCloud<pcl::PointXYZI>::Ptr basic_cloud_ptr(new pcl::PointCloud<pcl::PointXYZI>);
    pcl::io::loadPCDFile((info.filePath()).toStdString(), 
        *(basic_cloud_ptr));
    pcl::visualization::PointCloudColorHandlerGenericField<pcl::PointXYZI>multi_color(basic_cloud_ptr, "intensity");
    mViewer->removeAllPointClouds();
    mViewer->addPointCloud<pcl::PointXYZI>(basic_cloud_ptr, multi_color, "sample cloud");
    mViewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "sample cloud");

    mVtkWidget->update();

    mFileList->currentItem()->setSelected(true);

}

void PCLViewer::checkPass()
{
    QString commont = mCommentEdit->toPlainText();
    qDebug() << "pass: " << commont;

    int next = (mFileList->currentRow() + 1) % mFileList->count();
    mFileList->setCurrentRow(next);
    mCommentEdit->clear();
}

void PCLViewer::checkError()
{
    QString commont = mCommentEdit->toPlainText();
    qDebug() << "error: " << commont;

    int next = (mFileList->currentRow() + 1) % mFileList->count();
    mFileList->setCurrentRow(next);
    mCommentEdit->clear();
}