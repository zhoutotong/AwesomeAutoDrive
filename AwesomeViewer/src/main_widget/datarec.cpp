#include "datarec.h"
#include <QHeaderView>

#include <fstream>

namespace mainwidget
{

DataRecItem::DataRecItem(const QString &n, QObject *parent) : QObject(parent)
  , mNameLabel(new QLabel(n))
  , mStartBtn(new QPushButton("开始"))
  , mPauseBtn(new QPushButton("暂停"))
  , mStopBtn(new QPushButton("停止"))
  , mStatusLabel(new QLabel("停止"))
  , mCmdExec(new execctl::CmdExecable())
  , mCmd("")
  , mWidgetList({mNameLabel, mStartBtn, mStopBtn, mStatusLabel})
{
    // 设置label风格
    mNameLabel->setEnabled(false);
    mNameLabel->setStyleSheet("background:white; color:black");
    mStatusLabel->setEnabled(false);
    mStatusLabel->setStyleSheet("background:white; color:black");
    // 初始状态为停止
    mCurrentStatus = Stop;
    updateBtnStatus(mCurrentStatus);
    mStatusLabel->setText("停止");

    // 开始按钮
    connect(mStartBtn, &QPushButton::clicked, [this]{
        mCurrentStatus = Work;
        updateBtnStatus(Work);
        loadCmd();
        if(mCmdExec) mCmdExec->start(mCmd.toStdString());
        emit start();
    });
    // 暂停按钮
    connect(mPauseBtn, &QPushButton::clicked, [this]{
        mCurrentStatus = Pause;
        updateBtnStatus(Pause);
        emit pause();
    });
    // 停止按钮
    connect(mStopBtn, &QPushButton::clicked, [this]{
        mCurrentStatus = Stop;
        updateBtnStatus(Stop);
        if(mCmdExec) mCmdExec->stop();
        emit stop();
    });
}

DataRecItem::~DataRecItem()
{
    foreach(auto itor, mWidgetList)
    {
        delete itor;
    }
}

void DataRecItem::loadCmd()
{
    utilities::CfgFileHelper::checkAndCreateFile(utilities::CfgFileHelper::getDataRecCfgFile());
    // 从配置文件里载入
    YAML::Node root = YAML::LoadFile(utilities::CfgFileHelper::getDataRecCfgFile());
    // 检查root合法性
    if(root.IsMap())
    {
        std::string topicList;
        for(auto itor = root[mNameLabel->text().toStdString()]["topics"].begin(); itor != root[mNameLabel->text().toStdString()]["topics"].end(); itor++)
        {
            topicList += itor->as<std::string>() + " ";
        }
        std::string params = root[mNameLabel->text().toStdString()]["params"].as<std::string>();
        mCmd = "/opt/ros/melodic/lib/rosbag/record ";
        if (params.find_first_of("--buffsize") == std::string::npos && \
              params.find_first_of("-b") == std::string::npos)
        {
            mCmd += "--buffsize 256 ";
        }
        if (params.find_first_of("--chunksize") == std::string::npos)
        {
            mCmd += "--chunksize 768 ";
        }

        if (params.find_first_of("--output-prefix") == std::string::npos && \
              params.find_first_of("-o") == std::string::npos)
        {
            QString bagFilePath = QString::fromStdString(utilities::CfgFileHelper::getDataRecPath()) + "/" \
                + mNameLabel->text() + "/";
            utilities::APathHelper::createDir(bagFilePath.toStdString());
            mCmd += "--output-prefix " + bagFilePath + mNameLabel->text();
        }

        mCmd += QString::fromStdString(params);

        mCmd += " " + QString::fromStdString(topicList);
    }
}

void DataRecItem::updateBtnStatus(DataRecItemStatus s)
{
    switch(s)
    {
        case Stop:
            mStartBtn->setEnabled(true);
            mPauseBtn->setEnabled(false);
            mStopBtn->setEnabled(false);
            mStatusLabel->setText("停止");
        break;
        case Pause:
            mStartBtn->setEnabled(true);
            mPauseBtn->setEnabled(false);
            mStopBtn->setEnabled(true);
            mStatusLabel->setText("暂停");
        break;
        case Work: 
            mStartBtn->setEnabled(false);
            mPauseBtn->setEnabled(true);
            mStopBtn->setEnabled(true);
            mStatusLabel->setText("开始");
        break;
        default: break;
    }
}

DataRecWidget::DataRecWidget(QWidget *parent) : QWidget(parent)
  , mTable(new QTableWidget(this))
{
    // 初始化界面
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(mTable);
    mTable->horizontalHeader()->hide();
    mTable->verticalHeader()->hide();
    mTable->setColumnCount(4);
    DataRecItem *item = new DataRecItem("test");

    // 检查配置文件是否存在
    if(!utilities::CfgFileHelper::checkFileExist(utilities::CfgFileHelper::getDataRecCfgFile()))
    {
        // 如果不存在则新建，并初始化内容
        std::string fileDir = utilities::CfgFileHelper::getDataRecCfgFile();
        int cut = fileDir.find_last_of('/');
        std::string dir = fileDir.substr(0, cut);
        utilities::APathHelper::createDir(dir);
        fclose(fopen(fileDir.c_str(), "w+"));
        YAML::Node n = YAML::LoadFile(utilities::CfgFileHelper::getDataRecCfgFile());
        n = YAML::Load("{}");
        std::ofstream fout(utilities::CfgFileHelper::getDataRecCfgFile());
        fout << n;
    }
    // 从配置文件中添加任务
    loadItemFromCfgFile(QString::fromStdString(utilities::CfgFileHelper::getDataRecCfgFile()));

    // 添加更新按钮
    QPushButton *updateBtn = new QPushButton("重新载入");
    updateBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    layout->addWidget(updateBtn, Qt::AlignLeft);
    // 注册槽函数
    connect(updateBtn, &QPushButton::clicked, std::bind(&DataRecWidget::loadItemFromCfgFile
    , this, QString::fromStdString(utilities::CfgFileHelper::getDataRecCfgFile())));
}

DataRecWidget::~DataRecWidget()
{

}

void DataRecWidget::addItem(DataRecItem *item)
{
    mItemList.append(item);
    int rowCnt = mTable->rowCount();
    mTable->setRowCount(rowCnt + 1);
    for(int i = 0; i < item->getWidgetList().size(); i++)
    {
        mTable->setCellWidget(rowCnt, i, item->getWidgetList().at(i));
    }
}

void DataRecWidget::loadItemFromCfgFile(const QString &cfg)
{
    // 先检查是否有在工作的任务，有的话则不能更新
    for(int i = 0; i < mItemList.size(); i++)
    {
        if(Stop != mItemList.at(i)->getItemStatus())
        {
            QMessageBox::warning(this, "Warning", "当前有在工作的任务，请先关闭再执行本操作！");
            return;
        }
    }
    // 更新前清空当前的列表
    // 释放资源
    for(int i = 0; i < mItemList.size(); i++)
    {
        disconnect(mItemList.at(i));
        delete mItemList.at(i);
        mTable->removeRow(0);
    }
    // 清空维护的列表
    mItemList.clear();

    // 从配置文件里载入
    YAML::Node root = YAML::LoadFile(cfg.toStdString());
    // 检查root合法性
    if(!root.IsMap())
    {
        QMessageBox::critical(this, "Error", "配置文件错误，请清空重试");
    }
    for(auto itor = root.begin(); itor != root.end(); itor++)
    {
        QString name = QString::fromStdString(itor->first.as<std::string>());
        DataRecItem *item = new DataRecItem(name);
        addItem(item);
        connect(item, &DataRecItem::start, this, &DataRecWidget::start);
        connect(item, &DataRecItem::stop, this, &DataRecWidget::stop);
        connect(item, &DataRecItem::pause, this, &DataRecWidget::pause);

    }
}

void DataRecWidget::start()
{

}
void DataRecWidget::stop()
{

}
void DataRecWidget::pause()
{

}
}