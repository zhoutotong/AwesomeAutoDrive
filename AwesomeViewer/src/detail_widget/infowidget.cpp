#include "infowidget.h"
#include <QDebug>
#include "ros/package.h"

InfoWidget::InfoWidget(QString title, QWidget *parent) : QWidget(parent), mCurrentStatus(SHOW_NORMAL), mRootPath("")
  , mBriefWidget(nullptr)
  , mDetailWidget(nullptr)
{
    // set up layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    QHBoxLayout *topLayout = new QHBoxLayout();

    // this->setStyleSheet("background: white; color: white");
    mTitleLabel = new QLabel(title);
    QFont font;
    font.setBold(true);
    mTitleLabel->setFont(font);
    QPalette palette(mTitleLabel->palette());
    palette.setBrush(QPalette::Foreground, Qt::white);
    mTitleLabel->setPalette(palette);

    mTitleLabel->installEventFilter(this);
    mChangeStatusBtn = new QPushButton("切换");//(QPixmap(mRootPath + "/img/fullscreen.png"), "", this);
    mChangeStatusBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(mChangeStatusBtn, &QPushButton::clicked, this, &InfoWidget::statusChanged);

    QPushButton *updateBtn = new QPushButton("重载", this);
    updateBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(updateBtn, &QPushButton::clicked, this, &InfoWidget::updateStatus);

    topLayout->addWidget(mTitleLabel);
    topLayout->addWidget(updateBtn);
    topLayout->addWidget(mChangeStatusBtn);

    layout->addLayout(topLayout);
    this->setStatus(mCurrentStatus);
}
InfoWidget::~InfoWidget()
{
    if (mDetailWidget)
    {
        layout()->removeWidget(mDetailWidget);
        delete mDetailWidget;
        mDetailWidget = nullptr;
    }
    if (mBriefWidget)
    {
        layout()->removeWidget(mBriefWidget);
        delete mBriefWidget;
        mBriefWidget = nullptr;
    }
}

void InfoWidget::setStatus(const InfoWidget::Status &s)
{
    mCurrentStatus = s;
    QPalette palette(mTitleLabel->palette());

    switch (s)
    {
    case SHOW_MIN:

        break;
    case SHOW_NORMAL:
        // mChangeStatusBtn->setIcon(QPixmap(mRootPath + "/img/fullscreen.png"));
        palette.setBrush(QPalette::Foreground, Qt::white);
        mTitleLabel->setPalette(palette);
        _showBrief();
        break;
    case SHOW_MAX:
        // mChangeStatusBtn->setIcon(QPixmap(mRootPath + "/img/exit_fullscreen.png"));
        palette.setBrush(QPalette::Foreground, Qt::black);
        mTitleLabel->setPalette(palette);
        _showDetail();
        break;
    default:
        break;
    }
}

void InfoWidget::_showBrief()
{
    if (mBriefWidget)
    {
        layout()->removeWidget(mBriefWidget);
        delete mBriefWidget;
        mBriefWidget = nullptr;
    }
    if (mDetailWidget)
    {
        layout()->removeWidget(mDetailWidget);
        delete mDetailWidget;
        mDetailWidget = nullptr;
    }

    mBriefWidget = new QWidget();
    layout()->addWidget(mBriefWidget);
}
void InfoWidget::_showDetail()
{
    if (mBriefWidget)
    {
        layout()->removeWidget(mBriefWidget);
        delete mBriefWidget;
        mBriefWidget = nullptr;
    }

    if (mDetailWidget)
    {
        layout()->removeWidget(mDetailWidget);
        delete mDetailWidget;
        mDetailWidget = nullptr;
    }

    mDetailWidget = new QWidget();
    layout()->addWidget(mDetailWidget);
}

void InfoWidget::resetWidget()
{
    QString msg = "show brief window";
    QWidget *w = mBriefWidget;
    if(!w)
    {
        w = mDetailWidget;
        msg = "show detail window";
    } 
    if(!w) return;

    QVBoxLayout *layout = new QVBoxLayout(w);
    layout->setSpacing(0);
    layout->setMargin(0);
    layout->addWidget(new QTextEdit(msg + "\r\nStill Build...", w));
}

QString InfoWidget::getTitle()
{
    return mTitleLabel->text();
}

bool InfoWidget::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == mTitleLabel)
    {
        if (event->type() == QEvent::MouseButtonDblClick)
        {
            emit statusChanged();
            return true;
        }
    }
    return false;
}
