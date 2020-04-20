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

#include <iostream>
#include <fstream>
#include <functional>

#include <yaml-cpp/yaml.h>

class DataRecCfg : public QWidget
{
    Q_OBJECT
public:
    DataRecCfg(QWidget *parent = nullptr);
    ~DataRecCfg();

private:
    QTableWidget *mTableWidget;
    const QString mCfgFile;

    void loadFromCfgFile(const QString &cfg);
    void addItem(const QString &name, const QString &topics);


public slots:
    void removeItem(QWidget *index = nullptr);
    void updateItem(QWidget *index = nullptr);
};

#endif //_DATA_REC_CFG_H_