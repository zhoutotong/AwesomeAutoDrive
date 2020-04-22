#include "edittabwidget.h"
#include <QDebug>

EditTabWidget::EditTabWidget(QWidget *parent) : QTabWidget(parent)
  , mBar(new QTabBar(this))
  , mCurrentSelectTabIndex(-1)
  , mTabEditLine(new QLineEdit("", mBar))
  , mAddBtn(new QPushButton("Add", this))
{
    this->setTabBar(mBar);
    mBar->installEventFilter(this);
    installEventFilter(this);

    setCornerWidget(mAddBtn);
    connect(mAddBtn, &QPushButton::clicked, this, &EditTabWidget::tabAdded);

    mTabEditLine->setVisible(false);
    mBar->installEventFilter(this);
    mTabEditLine->installEventFilter(this);

    connect(mTabEditLine, &QLineEdit::returnPressed, this, &EditTabWidget::confirmLineEdit);
    connect(mBar, &QTabBar::currentChanged, this, &EditTabWidget::confirmLineEdit);

}

bool EditTabWidget::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == mBar)
    {
        if(event->type() == QEvent::MouseButtonDblClick)
        {
            mCurrentSelectTabIndex = mBar->currentIndex();
            QString currentTabText = mBar->tabText(mCurrentSelectTabIndex);

            mTabEditLine->setText(currentTabText);
            mTabEditLine->setVisible(true);

            mBar->setTabText(mCurrentSelectTabIndex, "");
            mBar->setTabButton(mBar->currentIndex(), QTabBar::LeftSide, mTabEditLine);
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            confirmLineEdit();
        }
    }
    else if(obj == this)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            confirmLineEdit();
        }
    }

    return false;
}

void EditTabWidget::confirmLineEdit()
{
    if(mCurrentSelectTabIndex != -1)
    {
        mBar->setTabButton(mCurrentSelectTabIndex, QTabBar::LeftSide, nullptr);
        mBar->setTabText(mCurrentSelectTabIndex, mTabEditLine->text());
        emit tabTextChanged(mCurrentSelectTabIndex, mTabEditLine->text());
    }
    mTabEditLine->setVisible(false);
    mCurrentSelectTabIndex = -1;
}

void EditTabWidget::cancelLineEdit()
{

}
