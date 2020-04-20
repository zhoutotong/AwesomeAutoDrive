#include "bag2datawidget.h"
#include <QDebug>

Bag2DataWidget::Bag2DataWidget(QWidget *parent) : QWidget(parent)
  , mDocFileListWidget(nullptr)
  , mOutputLine(nullptr)
  , mCurrentDir("./")
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    QHBoxLayout *centerLayout = new QHBoxLayout();
    layout->addLayout(centerLayout);

    //bag document management
    QVBoxLayout *docLayout = new QVBoxLayout();
    centerLayout->addLayout(docLayout);

    // open bag file dir btn
    QPushButton *openDirBtn = new QPushButton("OpenDir", this);
    connect(openDirBtn, &QPushButton::clicked, this, &Bag2DataWidget::openDocument);
    docLayout->addWidget(openDirBtn);

    // doc file list widget
    mDocFileListWidget = new QListWidget(this);
    docLayout->addWidget(mDocFileListWidget);

    // output dir set line
    QHBoxLayout *outputDirLayout = new QHBoxLayout();
    docLayout->addLayout(outputDirLayout);
    mOutputLine = new QLineEdit(QDir::currentPath(), this);
    outputDirLayout->addWidget(mOutputLine);
    QPushButton *openOuputDirBtn = new QPushButton("Open...");
    connect(openOuputDirBtn, &QPushButton::clicked, this, &Bag2DataWidget::setOutputDir);
    outputDirLayout->addWidget(openOuputDirBtn);
}

void Bag2DataWidget::openDocument()
{
    mCurrentDir = QFileDialog::getExistingDirectory(this, "Select Bag Dir", mCurrentDir);
    QDir dir(mCurrentDir);
    const QStringList filters = {"*.bag"};
    QFileInfoList infoList = dir.entryInfoList(filters);
    for(auto info = infoList.begin(); info != infoList.end(); info++)
    {
        QListWidgetItem *item = new QListWidgetItem(info->fileName(), mDocFileListWidget);
        item->setFlags(Qt::ItemIsEnabled|Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
    }
}

void Bag2DataWidget::setOutputDir()
{
    mOutputLine->setText(QFileDialog::getExistingDirectory(this, "Select Output Dir", mOutputLine->text()));
}
