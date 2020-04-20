#ifndef _DATA_REC_ITEM_H_
#define _DATA_REC_ITEM_H_

#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QDialog>
#include <QMessageBox>

#include <functional>

#include <yaml-cpp/yaml.h>

#include "utilities/cfgfilehelper.h"

namespace mainwidget
{

typedef enum {
    Stop = 0,
    Pause = 1,
    Work = 2,
}DataRecItemStatus;

class DataRecItem : public QObject
{
    Q_OBJECT
public:
    explicit DataRecItem(const QString &n, QObject *parent = nullptr);
    ~DataRecItem();

    inline const QList<QWidget*> getWidgetList() { return mWidgetList; }
    inline DataRecItemStatus getItemStatus() { return mCurrentStatus; }
private:


    QLabel *mNameLabel;
    QPushButton *mStartBtn;
    QPushButton *mPauseBtn;
    QPushButton *mStopBtn;
    QLabel *mStatusLabel;

    DataRecItemStatus mCurrentStatus;

    const QList<QWidget*> mWidgetList;

    void updateBtnStatus(DataRecItemStatus s);

};

class DataRecWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DataRecWidget(QWidget *parent = nullptr);
    ~DataRecWidget();

public:
    void addItem(DataRecItem *item);

private:
    QTableWidget *mTable;
    QList<DataRecItem*> mItemList;
    void loadItemFromCfgFile(const QString &cfg);
};


};

#endif // _DATA_REC_ITEM_H_
