#ifndef PACKAGESCTLWIDGET_H
#define PACKAGESCTLWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QPushButton>
#include <QLabel>

class PackagesCtlWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PackagesCtlWidget(QWidget *parent = nullptr);

private:
    QTableWidget *mTableWidget;

    void __addItem(const QString &package);

signals:

};

#endif // PACKAGESCTLWIDGET_H
