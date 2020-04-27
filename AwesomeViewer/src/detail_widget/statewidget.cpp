#include <QListWidgetItem>
#include "statewidget.h"
#include "infowidget.h"
#include "keystatisticsstatusinfowidget.h"
#include "networkinfowidget.h"
// #include "terminalwidget/terminalwidget.h"
#include "topicwatch.h"

#include "ros/ros.h"
#include "ros/package.h"

#include <QScrollArea>
#include <QScrollBar>
#include <QScreen>
#include <QApplication>
#include <QSettings>

#include <QDebug>

#include "utilities/cfgfilehelper.h"

StateWidget::StateWidget(QWidget *parent) : QWidget(parent)
{
    QPalette palette;
    palette.setBrush(QPalette::Background, Qt::black);
    this->setPalette(palette);
    
    __init();
}

bool StateWidget::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == mKeyStatisticsInfoWidget)
    {
        if (event->type() == QEvent::MouseButtonDblClick)
        {
            __showAllWidget();
            return true;
        }
    }
    return false;
}

void StateWidget::__init()
{
    // set up layout
    mLayout = new QVBoxLayout(this);
    setLayout(mLayout);

    // set up top layout
    mTopLayout = new QHBoxLayout();
    mLayout->addLayout(mTopLayout);

    mMainLayout = new QHBoxLayout();

    mKeyStatisticsInfoWidget = new KeyStatisticsStatusInfoWidget(this);
    mKeyStatisticsInfoWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mKeyStatisticsInfoWidget->installEventFilter(this);
    mMainLayout->addWidget(mKeyStatisticsInfoWidget);

    // set up info recorder layout
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setFixedWidth(QApplication::screens().at(0)->size().width() * 0.35);
    scrollArea->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);


    // scroll area's widget
    QWidget *infoItemsWidget = new QWidget(this);
    infoItemsWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    infoItemsWidget->setFixedWidth(scrollArea->width() - 20);
    mInfoLayout = new QVBoxLayout(infoItemsWidget);

    QString cfgFile = QString::fromStdString(utilities::CfgFileHelper::getModelCfgFile());

    // 加载现有模块
    if(utilities::CfgFileHelper::checkFileExist(cfgFile.toStdString()))
    {
        YAML::Node modNode = YAML::LoadFile(cfgFile.toStdString());

        for(auto itor = modNode.begin(); itor != modNode.end(); itor++)
        {
            __addInfoWidget(mInfoLayout, new statewidgets::TopicWatch(
                QString::fromStdString(itor->second.as<std::string>()),
                QString::fromStdString(itor->first.as<std::string>())));
        }
    }

    scrollArea->setWidget(infoItemsWidget);
    // set up terminal layout
    QHBoxLayout *bottomLayout = new QHBoxLayout();
    mLayout->addLayout(bottomLayout);
    // QWidget *terminalWidget = new TerminalWidget();
    // bottomLayout->addWidget(terminalWidget);

    mTopLayout->addWidget(scrollArea);
    mTopLayout->addLayout(mMainLayout);
}

void StateWidget::__addInfoWidget(QLayout *l, InfoWidget *w)
{
    w->resetWidget();
    w->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    l->addWidget(w);
    connect(w, &InfoWidget::statusChanged, this, &StateWidget::changeStatus);
}

void StateWidget::__showAllWidget()
{
    QWidget *widget = mMainLayout->itemAt(0)->widget();

    if (widget == mKeyStatisticsInfoWidget)
    {
        return;
    }

    // widget->setParent(nullptr);
    mInfoLayout->replaceWidget(mKeyStatisticsInfoWidget, widget);

    static_cast<InfoWidget *>(widget)->setStatus(InfoWidget::Status::SHOW_NORMAL);
    mMainLayout->addWidget(mKeyStatisticsInfoWidget);
    // widget->setParent(this);
}

void StateWidget::__showOneWidget(QWidget *w)
{
    QWidget *widget = mMainLayout->itemAt(0)->widget();
    mMainLayout->removeWidget(widget);
    // widget->setParent(nullptr);

    if (widget == mKeyStatisticsInfoWidget)
    {
        qDebug() << w << widget;
        mInfoLayout->replaceWidget(w, widget);
    }
    else
    {
        mInfoLayout->replaceWidget(mKeyStatisticsInfoWidget, widget);
        mInfoLayout->replaceWidget(w, mKeyStatisticsInfoWidget);
        static_cast<InfoWidget *>(widget)->setStatus(InfoWidget::Status::SHOW_NORMAL);
    }

    // set current clicked widget to main widget
    mMainLayout->addWidget(w);
}

void StateWidget::changeStatus()
{
    InfoWidget *w = static_cast<InfoWidget *>(sender());

qDebug() << "change widget: " << w;
    if (w->getStatus() == InfoWidget::Status::SHOW_MAX)
    {
        w->setStatus(InfoWidget::Status::SHOW_NORMAL);
        __showAllWidget();
    }
    else if (w->getStatus() == InfoWidget::Status::SHOW_NORMAL)
    {
        w->setStatus(InfoWidget::Status::SHOW_MAX);
        __showOneWidget(w);
    }
    w->resetWidget();
}
