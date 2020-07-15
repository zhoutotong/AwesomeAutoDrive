#ifndef _DATA_REC_CFG_H_
#define _DATA_REC_CFG_H_

#include <QWidget>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QListWidget>
#include <QSplitter>
#include <QEvent>
#include <QInputDialog>

#include <iostream>
#include <fstream>
#include <functional>

#include <yaml-cpp/yaml.h>

#include "utilities/rostools.h"

class DataRecCfg : public QWidget
{
    Q_OBJECT
public:
    DataRecCfg(QWidget *parent = nullptr);
    ~DataRecCfg();

protected:
    bool eventFilter(QObject *obj, QEvent *e);

private:
    QTableWidget *mTableWidget;
    const QString mCfgFile;
    QListWidget *mTopicListWidget;
    QLineEdit *mSelectedLine;

    void loadFromCfgFile(const QString &cfg);
    void addItem(const QString &name, const QString &topics, const QString &params);


public slots:
    void removeItem(QWidget *index = nullptr);
    void updateItem(QWidget *index = nullptr);
    void updateTopicList();
    void changeTopic2Item(const QModelIndex &index);
};

#endif //_DATA_REC_CFG_H_