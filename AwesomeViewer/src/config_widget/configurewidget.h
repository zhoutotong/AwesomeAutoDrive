#ifndef CONFIGUREWIDGET_H
#define CONFIGUREWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QTableWidgetItem>
#include <QTabWidget>
#include <QLineEdit>
#include <QLabel>

class ConfigureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ConfigureWidget(QWidget *parent = nullptr);

private:


signals:

};

#endif // CONFIGUREWIDGET_H
