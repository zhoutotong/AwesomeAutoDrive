#ifndef _RVIZ_VIEW_H_
#define _RVIZ_VIEW_H_

#include <QWidget>
#include <QObject>
#include <QEvent>
#include <QMouseEvent>
#include <QMenu>
#include <QAction>
#include <QDialog>
#include <QVariant>
#include <QFileDialog>
#include <QMessageBox>

#include <functional>


// #include "ros/package.h"
#include "rviz/yaml_config_reader.h"
#include "rviz/yaml_config_writer.h"

#include "rviz/tool_manager.h"
#include "rviz/properties/property.h"
#include "rviz/tool.h"
#include "jsk_rviz_plugins/overlay_image_display.h"
#include "jsk_rviz_plugins/overlay_text_display.h"
#include "doublevaluemeter.h"

#include <QActionGroup>

#include <QResizeEvent>

namespace rviz
{
    class Display;
    class RenderPanel;
    class VisualizationManager;
}

#define CONFIG_EXTENSION "rviz"
#define CONFIG_EXTENSION_WILDCARD "*." CONFIG_EXTENSION

class RvizView : public QWidget
{
    Q_OBJECT
public:
    explicit RvizView(QWidget *parent = nullptr);
    ~RvizView();

private:
    rviz::VisualizationManager *manager_;
    rviz::RenderPanel *render_panel_;
    rviz::Display *setup_display;
    rviz::Config config_;

    jsk_rviz_plugins::OverlayTextDisplay *moduleStatusInfoPanel;
    jsk_rviz_plugins::OverlayTextDisplay *workInfoPanel;


    hmi_visualization::DoubleValueMeter *steeringMeter;
    hmi_visualization::DoubleValueMeter *speedMeter;
    jsk_rviz_plugins::OverlayImageDisplay *imageDisplay;

    QMenu *menu_;
    QActionGroup *tools_act_group_;
    bool is_show_menu_;
    QString config_file_;

    void __setupMenu();
    QAction* __addAction(QMenu *menu, const QString name, std::function<void(bool)> cb, bool checkable = false);
    void __updateToolGroup();


    // 右键菜单响应函数
    void __showDisplayPanel();
    void __showViewsPanel();
    void __addTools();
    void __loadCfgFile();


    void logoutModelData(rviz::Property *p);
    QString convertType(QVariant value);

protected:
    bool eventFilter(QObject *obj, QEvent *e) override;
    void resizeEvent(QResizeEvent *e) override;

public slots:
    // void readChangedData(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles = QVector<int>());
};

#endif // end of _RVIZ_VIEW_H_