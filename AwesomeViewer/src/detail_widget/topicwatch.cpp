#include "topicwatch.h"
#include <functional>
#include <QDebug>
#include <QPalette>
#include <signal.h>
#include <sys/types.h>
#include <QList>
#include <QSemaphore>
#include <QSettings>

#include "ros/ros.h"
#include "ros/package.h"


#define SIZE_OF_STATE_LIST (10)
QList<hmi_msgs::all_state> gAllStateList;
QSemaphore gFreeSem(SIZE_OF_STATE_LIST);
QSemaphore gUsedSem(0);
    
QStringList gTableHeaders = {"监控名称", "话题", "频率值", "参数", "参数值"};

namespace statewidgets {

BriefWidget::BriefWidget(const QString &modelLabel, QWidget *parent) : BaseInfoWidget(modelLabel, parent)
  , mDataWidget(new QTableWidget(0, 0, this))
{
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, Qt::white);

    this->setStyleSheet("background:white");

    setLayout(new QVBoxLayout(this));
    layout()->setMargin(0);
    layout()->setSpacing(0);
    layout()->addWidget(mDataWidget);
    mDataWidget->setBackgroundRole(QPalette::Light);
    
    mDataWidget->setHorizontalHeaderLabels(gTableHeaders);
    mDataWidget->setHorizontalHeaderLabels(gTableHeaders);
    mDataWidget->setColumnCount(gTableHeaders.size());
    mDataWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    mDataWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    mDataWidget->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);

}
BriefWidget::~BriefWidget()
{

}
void BriefWidget::updateData(const hmi_msgs::all_state &datas)
{
    if(!mDataWidget) return;
    mDataWidget->clear();
    mDataWidget->setHorizontalHeaderLabels(gTableHeaders);
    mDataWidget->setColumnCount(gTableHeaders.size());
    mDataWidget->setRowCount(datas.states.size());

    int i = 0;
    foreach(hmi_msgs::node_state item, datas.states)
    {
        int m = 0;
        QTableWidgetItem *tbItem = nullptr;
        tbItem = new QTableWidgetItem(QString::fromStdString(item.msg_name));
        mDataWidget->setItem(i, m++, tbItem);
        tbItem = new QTableWidgetItem(QString::fromStdString(item.msg_name));
        mDataWidget->setItem(i, m++, tbItem);
        tbItem = new QTableWidgetItem(QString("%1").arg(item.hz));
        if(!item.hz_state)
        {
            tbItem->setTextColor(Qt::red);
        }
        mDataWidget->setItem(i, m++, tbItem);
        tbItem = new QTableWidgetItem(QString("%1").arg(item.param_value));
        if(!item.param_state)
        {
            tbItem->setTextColor(Qt::red);
        }
        mDataWidget->setItem(i, m++, tbItem);
    
        i++;
    }
}

void BriefWidget::updateData(const NodeDataMapDef &dataMap)
{
    if (!mDataWidget)
        return;
    int rowCount = 0;
    mDataWidget->clear();
    int i = 0;
    foreach (auto itor, dataMap.keys())
    {
        mDataWidget->setHorizontalHeaderLabels(gTableHeaders);
        mDataWidget->setColumnCount(gTableHeaders.size());

        rowCount += dataMap[itor].states.size();
        mDataWidget->setRowCount(rowCount);

        foreach (hmi_msgs::node_state item, dataMap[itor].states)
        {
            int m = 0;
            QTableWidgetItem *tbItem = nullptr;

            // 监控名称参数
            QString watchParamName = QString::fromStdString(mNodeList[item.msg_name]["params"][item.param_name]["name"].as<std::string>());
            tbItem = new QTableWidgetItem(watchParamName);
            mDataWidget->setItem(i, m++, tbItem);
            // 更新节点名称列
            QString nodeName = QString::fromStdString(item.msg_name);
            tbItem = new QTableWidgetItem(nodeName);
            mDataWidget->setItem(i, m++, tbItem);

            // 更新节点频率列
            tbItem = new QTableWidgetItem(QString("%1").arg(item.hz));
            if (!item.hz_state)
            {
                tbItem->setTextColor(Qt::red);
            }
            mDataWidget->setItem(i, m++, tbItem);

            // 更新参数名称列
            tbItem = new QTableWidgetItem(QString::fromStdString(item.param_name));
            mDataWidget->setItem(i, m++, tbItem);

            // 更新参数值列
            tbItem = new QTableWidgetItem(QString("%1").arg(item.param_value));
            if (!item.param_state)
            {
                tbItem->setTextColor(Qt::red);
            }
            mDataWidget->setItem(i, m++, tbItem);

            i++;
        }
    }
}

DetailWidget::DetailWidget(const QString &modelLabel, QWidget *parent) : BaseInfoWidget(modelLabel, parent)
  , mDataWidget(new QTableWidget(0, 0, this))
{
    setObjectName(modelLabel);
    this->setStyleSheet("background:white");

    setLayout(new QVBoxLayout(this));
    layout()->setMargin(0);
    layout()->setSpacing(0);
    layout()->addWidget(mDataWidget);
    mDataWidget->setBackgroundRole(QPalette::Light);
}
DetailWidget::~DetailWidget()
{
qDebug() << __FUNCTION__ << " released " << __LINE__;
}
void DetailWidget::updateData(const hmi_msgs::all_state &datas)
{
    if(!mDataWidget) return;
    mDataWidget->clear();
    mDataWidget->setHorizontalHeaderLabels(gTableHeaders);
    mDataWidget->setColumnCount(gTableHeaders.size());
    mDataWidget->setRowCount(datas.states.size());

    int i = 0;
    foreach(hmi_msgs::node_state item, datas.states)
    {
        int m = 0;
        QTableWidgetItem *tbItem = nullptr;
        tbItem = new QTableWidgetItem(QString::fromStdString(item.msg_name));
        mDataWidget->setItem(i, m++, tbItem);
        tbItem = new QTableWidgetItem(QString("%1").arg(item.hz));
        if(!item.hz_state)
        {
            tbItem->setTextColor(Qt::red);
        }
        mDataWidget->setItem(i, m++, tbItem);
        tbItem = new QTableWidgetItem(QString("%1").arg(item.param_value));
        if(!item.param_state)
        {
            tbItem->setTextColor(Qt::red);
        }
        mDataWidget->setItem(i, m++, tbItem);
    
        i++;
    }
}

void DetailWidget::updateData(const NodeDataMapDef &dataMap)
{

}

TopicWatch::TopicWatch(const QString &modName, const QString &modeLabel, QWidget *parent) : InfoWidget(modName, parent)
  , mIsWatching(false)
  , mCurWidget(nullptr)
  , mModName(modName)
{
    mIsWatching = true;
    setBackgroundRole(QPalette::Light);
    setObjectName(modeLabel);

    connect(this, &TopicWatch::updateStatus, this, &TopicWatch::updateModelCfg);

    std::string im = modeLabel.toStdString() + "_node";
    mTopicWatchThreadList.append(new std::thread([this, im] {
        ros::NodeHandle _n;
        ros::Subscriber sub = _n.subscribe<hmi_msgs::all_state>(im, 
                                100, std::bind(&TopicWatch::__statusWatchCb, this, std::placeholders::_1, QString::fromStdString(im)));
        ros::Rate loop(10);
        while (mIsWatching)
        {
            // ros::spinOnce();
            loop.sleep();
        }
        std::cout << im << " topic watch exit!!!" << std::endl;
        return;
    }));


    mWatchTimer = new QTimer();
    connect(mWatchTimer, &QTimer::timeout, this, &TopicWatch::updateData);
    mWatchTimer->start(500);
}
TopicWatch::~TopicWatch()
{
    mIsWatching = false;
    foreach(std::thread* th, mTopicWatchThreadList)
    {
        th->join();
        delete th;
        th = nullptr;
    }

}

void TopicWatch::resetWidget()
{
    QWidget *w = nullptr;
    QString msg;
    if(briefWidget() && getStatus() == Status::SHOW_NORMAL)
    {
        // 简化消息界面
        w = briefWidget();
        mCurWidget = new BriefWidget(objectName(), w);
        msg = "show brief window";
    }
    else if(detailWidget() && getStatus() == Status::SHOW_MAX)
    {
        // 详细消息界面
        w = detailWidget();
        mCurWidget = new DetailWidget(objectName(), w);
        msg = "show detail window";
    } else return;
    QVBoxLayout *layout = new QVBoxLayout(w);
    layout->setSpacing(0);
    layout->setMargin(0);
    layout->addWidget(mCurWidget);
}

void TopicWatch::__statusWatchCb(const hmi_msgs::all_stateConstPtr &msg, const QString &nodeName)
{
    if(!msg) return;
    mNodeDataMap[nodeName] = hmi_msgs::all_state(*msg);
}

void TopicWatch::updateData()
{
    mCurWidget->updateData(mNodeDataMap);
}

void TopicWatch::updateModelCfg()
{
    // 关闭正在监测的线程
    execctl::ExecCtl::get_instance().stop(objectName().toStdString());

    // 更新脚本
    std::string cfgFile = utilities::CfgFileHelper::getModelCfgDir() + objectName().toStdString() + ".yaml";
    std::string script = utilities::CfgFileHelper::getModelCfgDir() + objectName().toStdString() + ".py";
    utilities::RosTools::generateTopicWatch(objectName().toStdString(), cfgFile, script);

    // 启动监测线程
    execctl::ExecCtl::get_instance().start(objectName().toStdString());
}

}// end of statewidget