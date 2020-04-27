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
    
QStringList gTableHeaders = {"话题", "频率值", "参数", "参数值"};

namespace statewidgets {

BriefWidget::BriefWidget(QWidget *parent) : BaseInfoWidget(parent)
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
    mDataWidget->setRowCount(2);
}
BriefWidget::~BriefWidget()
{
qDebug() << __FUNCTION__ << " released " << __LINE__;
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

void BriefWidget::updateData(const QMap<QString, hmi_msgs::all_state> &dataMap)
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
        // qDebug() << itor << dataMap[itor].states.size() << rowCount;

        foreach (hmi_msgs::node_state item, dataMap[itor].states)
        {
            // qDebug() << item.hz << QString::fromStdString(item.msg_name)
            // << QString::fromStdString(item.param_name) << item.param_value;
            int m = 0;
            QTableWidgetItem *tbItem = nullptr;
            QString nodeName = itor;
            QStringList nodeNameList = nodeName.split("_");
            nodeName.remove(nodeNameList.at(0) + "_");
            nodeName.remove(QString("_") + nodeNameList.at(nodeNameList.size() - 1));
            tbItem = new QTableWidgetItem(nodeName);
            mDataWidget->setItem(i, m++, tbItem);
            tbItem = new QTableWidgetItem(QString::fromStdString(item.msg_name));
            mDataWidget->setItem(i, m++, tbItem);
            tbItem = new QTableWidgetItem(QString("%1").arg(item.hz));
            if (!item.hz_state)
            {
                tbItem->setTextColor(Qt::red);
            }
            mDataWidget->setItem(i, m++, tbItem);
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

DetailWidget::DetailWidget(QWidget *parent) : BaseInfoWidget(parent)
  , mDataWidget(new QTableWidget(0, 0, this))
{
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

void DetailWidget::updateData(const QMap<QString, hmi_msgs::all_state> &dataMap)
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

    QString rootPath = QString::fromStdString(ros::package::getPath("hmi_msgs"));
    QSettings *set = new QSettings(rootPath + "/config/ros_node/cfg.ini", QSettings::IniFormat);
    QStringList nodeList = set->value(modName + "/NodeList").toStringList();
    qDebug() << __FUNCTION__ << __LINE__ << modName << nodeList;
    delete set;
    set = nullptr;

    connect(this, &TopicWatch::updateStatus, this, &TopicWatch::updateModelCfg);

    foreach(QString item, nodeList)
    {
        QString im = mModName + "_" + item + "_status";
        mTopicWatchThreadList.append(new std::thread([this, &im] {
            ros::NodeHandle _n;
            std::cout << im.toStdString() << " start watch..." << std::endl;
            ros::Subscriber sub = _n.subscribe<hmi_msgs::all_state>(im.toStdString(), 
                                  100, std::bind(&TopicWatch::__statusWatchCb, this, std::placeholders::_1, im));
            ros::Rate loop(10);
            while (mIsWatching)
            {
                ros::spinOnce();
                loop.sleep();
            }
            qDebug() << im << " topic watch exit!!!";
            return;
        }));
        usleep(50);
    }

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
        mCurWidget = new BriefWidget(w);
        msg = "show brief window";
    }
    else if(detailWidget() && getStatus() == Status::SHOW_MAX)
    {
        // 详细消息界面
        w = detailWidget();
        mCurWidget = new DetailWidget(w);
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
    // 生产者
    gFreeSem.acquire(1);
    gAllStateList.append(*msg);
    gUsedSem.release(1);

    mNodeDataMap[nodeName] = *msg;
}

void TopicWatch::updateData()
{
    mCurWidget->updateData(mNodeDataMap);
    if(!gUsedSem.tryAcquire()) return;
    auto itor = gAllStateList.begin();

    if(mCurWidget) mCurWidget->updateData(*itor);
    gAllStateList.pop_front();

    gFreeSem.release(1);
}

void TopicWatch::updateModelCfg()
{
    // 关闭正在监测的线程
    execctl::ExecCtl::get_instance().stop(objectName().toStdString());

    // 更新脚本
    std::string cfgFile = utilities::CfgFileHelper::getModelCfgDir() + objectName().toStdString() + ".yaml";
    std::string script = utilities::CfgFileHelper::getModelCfgDir() + objectName().toStdString() + ".py";
    utilities::RosTools::generateTopicWatch(cfgFile, script);

    // 启动监测线程
    execctl::ExecCtl::get_instance().start(objectName().toStdString());
}

}// end of statewidget