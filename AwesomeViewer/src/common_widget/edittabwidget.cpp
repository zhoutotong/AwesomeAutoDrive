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

    connect(this, &EditTabWidget::tabCloseRequested, [this](int index){
        confirmLineEdit();
    });

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
            mTabEditLine->setFocus();

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
    else if(obj == mTabEditLine)
    {
        if(event->type() == QEvent::FocusOut)
        {
            confirmLineEdit();
        }
    }

    if(event->type() == QEvent::Close)
    {
        qDebug() << "tab closed";
    }

    return false;
}

void EditTabWidget::confirmLineEdit()
{
    if(mCurrentSelectTabIndex != -1)
    {
        const int index = mCurrentSelectTabIndex;
        QString lastStr = mBar->tabText(index);
        mBar->setTabButton(index, QTabBar::LeftSide, nullptr);
        mBar->setTabText(index, mTabEditLine->text());
        qDebug() << "emit: " << index;
        emit tabTextChanged(index, mTabEditLine->text(), lastStr);
    }
    mTabEditLine->setVisible(false);
    mCurrentSelectTabIndex = -1;
}

void EditTabWidget::cancelLineEdit()
{

}
