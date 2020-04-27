#pragma once

#include <QWidget>
#include <QTimer>
#include <QTableWidget>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QList>
#include <thread>
#include <pthread.h>

#include <QMap>

#include "infowidget.h"
#include "utilities/cfgfilehelper.h"
#include "utilities/rostools.h"
#include "utilities/execctl.h"

#include "ros/ros.h"
#include "hmi_msgs/all_state.h"

namespace statewidgets {

// 简要消息视图
class BaseInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BaseInfoWidget(QWidget *parent = nullptr) : QWidget(parent){}
    ~BaseInfoWidget(){}

public:
    virtual void updateData(const hmi_msgs::all_state &datas) = 0;
    virtual void updateData(const QMap<QString, hmi_msgs::all_state> &dataMap) = 0;
}; // end of BaseInfoWidget

// 详细消息视图
class BriefWidget : public BaseInfoWidget
{
    Q_OBJECT
public:
    explicit BriefWidget(QWidget *parent = nullptr);
    ~BriefWidget();

public:
    void updateData(const hmi_msgs::all_state &datas);
    void updateData(const QMap<QString, hmi_msgs::all_state> &dataMap);


private:
    QTableWidget *mDataWidget;
}; // end of BriefWidget


class DetailWidget : public BaseInfoWidget
{
    Q_OBJECT
public:
    explicit DetailWidget(QWidget *parent = nullptr);
    ~DetailWidget();

public:
    void updateData(const hmi_msgs::all_state &datas);
    void updateData(const QMap<QString, hmi_msgs::all_state> &dataMap);

private:
    QTableWidget *mDataWidget;
}; // end of DetailWidget

class TopicWatch : public InfoWidget
{
    Q_OBJECT
public:
    explicit TopicWatch(const QString &modName, const QString &modeLabel, QWidget *parent = nullptr);
    ~TopicWatch();

    void resetWidget();

private:
    void __statusWatchCb(const hmi_msgs::all_stateConstPtr &msg, const QString &nodeName);


private:
    bool mIsWatching;
    QList<std::thread *> mTopicWatchThreadList;
    QTimer *mWatchTimer;
    const QString mModName;

    BaseInfoWidget *mCurWidget;


    QMap<QString, hmi_msgs::all_state> mNodeDataMap;

public slots:
    void updateData();
    void updateModelCfg();
};// end of TopicWatch


}// end of statewidgets