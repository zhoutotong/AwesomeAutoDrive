#ifndef MODELCONFIGWIDGET_H
#define MODELCONFIGWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "common_widget/edittabwidget.h"

class ModelConfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ModelConfigWidget(QWidget *parent = nullptr);

private:
    EditTabWidget *mTableWidget;
signals:

};

#endif // MODELCONFIGWIDGET_H
