#ifndef _MAIN_WIDGET_H_
#define _MAIN_WIDGET_H_

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QSplitter>
#include <QResizeEvent>

#include "datarec.h"


namespace mainwidget
{
class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

protected:

};    
};

#endif // _MAIN_WIDGET_H_
