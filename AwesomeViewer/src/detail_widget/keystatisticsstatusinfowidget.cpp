#include "keystatisticsstatusinfowidget.h"

KeyStatisticsStatusInfoWidget::KeyStatisticsStatusInfoWidget(QWidget *parent) : QWidget(parent)
  , mTableWidget(nullptr)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    setLayout(layout);

//    layout->addWidget(new QLabel("key statistics status info", this));
    mTableWidget = new QTableWidget(4, 3, this);
    mTableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    mTableWidget->installEventFilter(this);
    // set up background color
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, "#ffffff");
    this->setPalette(palette);
    layout->addWidget(mTableWidget);

    QTableWidgetItem *cubesHeaderItem = new QTableWidgetItem(tr("人工接管次数"));
    cubesHeaderItem->setIcon(QIcon(QPixmap(":/Images/cubed.png")));
    cubesHeaderItem->setTextAlignment(Qt::AlignHCenter);
    mTableWidget->setItem(0, 0, cubesHeaderItem);

    cubesHeaderItem = new QTableWidgetItem(tr("里程统计"));
    cubesHeaderItem->setIcon(QIcon(QPixmap(":/Images/cubed.png")));
    cubesHeaderItem->setTextAlignment(Qt::AlignHCenter);
    mTableWidget->setItem(1, 0, cubesHeaderItem);

    cubesHeaderItem = new QTableWidgetItem(tr("作业次数"));
    cubesHeaderItem->setIcon(QIcon(QPixmap(":/Images/cubed.png")));
    cubesHeaderItem->setTextAlignment(Qt::AlignHCenter);
    mTableWidget->setItem(2, 0, cubesHeaderItem);
}

//bool KeyStatisticsStatusInfoWidget::eventFilter(QObject *obj, QEvent *event)
//{
//  return false;
//}

