#ifndef _MAIN_WIDGET_H_
#define _MAIN_WIDGET_H_

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QSplitter>
#include <QResizeEvent>

#include "datarec.h"

#include "rviz/visualization_frame.h"
#include "rvizview/visualizer_app.h"


namespace mainwidget
{
class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(const rviz::VisualizerApp *vapp, QWidget *parent = nullptr);
    ~MainWidget();

protected:

};    
};

#endif // _MAIN_WIDGET_H_
