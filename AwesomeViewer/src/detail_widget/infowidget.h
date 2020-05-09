#ifndef INFOWIDGET_H
#define INFOWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QEvent>

class InfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit InfoWidget(QString title, QWidget *parent = nullptr);
    ~InfoWidget();

public:
    typedef enum _Status
    {
        SHOW_MIN = 0,
        SHOW_NORMAL = 1,
        SHOW_MAX = 2,
    } Status;
    void setStatus(const Status &s);
    inline Status getStatus() { return mCurrentStatus; }
    QString getTitle();

    inline QWidget* briefWidget() { return mBriefWidget; }
    inline QWidget* detailWidget() { return mDetailWidget; }

    virtual void resetWidget();


private:
    void _showBrief();
    void _showDetail();

private:
    const QString mRootPath;

    QPushButton *mChangeStatusBtn;
    QLabel *mTitleLabel;
    Status mCurrentStatus;

    QWidget *mBriefWidget;
    QWidget *mDetailWidget;

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

signals:
    void statusChanged();
    void updateStatus();
public slots:
};

#endif // INFOWIDGET_H
