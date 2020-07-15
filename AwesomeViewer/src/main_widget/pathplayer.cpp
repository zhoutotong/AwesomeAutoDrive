#include "pathplayer.hpp"
#include <QHeaderView>

PathPlayer::PathPlayer(QWidget *parent) : QWidget(parent)
  , mPathListWidget(nullptr)
  , mPathSelectGroup(new QButtonGroup(this))
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    mPathListWidget = new QTableWidget(this);
    layout->addWidget(mPathListWidget);

    mPathSelectGroup->setExclusive(true);


    mPathListWidget->horizontalHeader()->hide();
    mPathListWidget->verticalHeader()->hide();

    PathItem item;
    item.clear();createPathItem(item);addItem(item);
    item.clear();createPathItem(item);addItem(item);
    item.clear();createPathItem(item);addItem(item);
    item.clear();createPathItem(item);addItem(item);

}

PathPlayer::~PathPlayer()
{

}

void PathPlayer::createPathItem(PathItem &item)
{
    QCheckBox *pathSelectBox = new QCheckBox("test", this);
    mPathSelectGroup->addButton(pathSelectBox);
    QPushButton *statusBtn = new QPushButton("播放", this);
    connect(statusBtn, &QPushButton::clicked, this, &PathPlayer::changePathStatus);

    QPushButton *startBtn = new QPushButton("启动", this);

    statusBtn->setCheckable(true);
    QPushButton *delBtn = new QPushButton("删除", this);


    item.append(pathSelectBox);
    item.append(statusBtn);
    item.append(startBtn);
    item.append(delBtn);
}

void PathPlayer::addItem(const PathItem &item)
{
    mPathListWidget->setColumnCount(item.size());
    mPathListWidget->setRowCount(mPathListWidget->rowCount() + 1);
    int i = 0;
    for(auto itor = item.begin(); itor != item.end(); itor++)
    {
        mPathListWidget->setCellWidget(mPathListWidget->rowCount() - 1, i++, *itor);
    }
}

void PathPlayer::changePathStatus()
{
    QPushButton *btn = static_cast<QPushButton*>(sender());
    if(btn->isChecked())
    {
        btn->setText("录制");
    } else
    {
        btn->setText("播放");
    }
    
}

