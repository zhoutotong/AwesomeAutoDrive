#include "rviz/visualization_manager.h"
#include "rviz/render_panel.h"
#include "rviz/display.h"
#include "rviz/properties/property.h"
#include "rviz/display_group.h"

#include "rvizview.h"
#include <ros/ros.h>
#include "rviz/display_factory.h"
#include "rviz/add_display_dialog.h"
#include "rviz/displays_panel.h"
#include "rviz/selection_panel.h"
#include "rviz/selection/selection_manager.h"
#include "rviz/properties/property_tree_model.h"
#include "rviz/new_object_dialog.h"

#include <QApplication>
#include <QVBoxLayout>
#include <QStyleOptionViewItem>
#include <QDebug>

#include <QTimer>

#include "utilities/cfgfilehelper.h"
#include "utilities/rostools.h"

RvizView::RvizView(QWidget *parent) : QWidget(parent), setup_display(nullptr), is_show_menu_(false)
  , config_file_(QString::fromStdString(utilities::CfgFileHelper::getRvizCfgFile()))
{
    // 初始化界面显示
    QVBoxLayout *main_layout = new QVBoxLayout(this);
    main_layout->setMargin(0);
    main_layout->setSpacing(0);
    setLayout(main_layout);

    // 创建 manager
    render_panel_ = new rviz::RenderPanel();
    render_panel_->installEventFilter(this);
    manager_ = new rviz::VisualizationManager(render_panel_);
    render_panel_->initialize(manager_->getSceneManager(), manager_);
    manager_->initialize();
    manager_->startUpdate();

    // init tool manager
    rviz::ToolManager *tool_manager = manager_->getToolManager();
    tool_manager->setCurrentTool(tool_manager->getTool(0));

    // 添加网格
    grid_ = manager_->createDisplay("rviz/Grid", "Grid", false);
    ROS_ASSERT(grid_ != nullptr);

    // Configure the GridDisplay the way we like it.
    grid_->subProp("Line Style")->setValue("Lines");
    grid_->subProp("Color")->setValue(QColor(Qt::gray));

    grid_->subProp("Line Style")->subProp("Line Width")->setValue(0.05f);
    grid_->subProp("Cell Size")->setValue(1.0f);
    grid_->subProp("Plane")->setValue("xy");

    main_layout->addWidget(render_panel_);

    // 检查配置文件是否存在
    if (!utilities::CfgFileHelper::checkFileExist(config_file_.toStdString()))
    {
        // 如果不存在则新建，并初始化内容
        manager_->save(config_);
        rviz::YamlConfigWriter writer;
        QFile::remove(config_file_);
        writer.writeFile(config_, config_file_);

        if (writer.error())
        {
            printf("%s", qPrintable(writer.errorMessage()));
        }
    }

    // 加载配置文件
    if (QFile::exists(config_file_))
    {
        rviz::YamlConfigReader reader;
        reader.readFile(config_, config_file_);
        if (reader.error())
        {
            qDebug() << qPrintable(reader.errorMessage());
            return;
        }
        manager_->load(config_);
    }

    // add steering display
    moduleStatusInfoPanel =
        new jsk_rviz_plugins::OverlayTextDisplay();
    if( moduleStatusInfoPanel)
    {
        manager_->addDisplay(moduleStatusInfoPanel, true);
        moduleStatusInfoPanel->setName("ModuleStatusInfoPanel");
        // moduleStatusInfoPanel->setTopic("/module_status_info", "hmi_msgs/overlay_text");
    }


    workInfoPanel = 
        new jsk_rviz_plugins::OverlayTextDisplay();
    if( workInfoPanel)
    {
        manager_->addDisplay(workInfoPanel, true);
        workInfoPanel->setName("WorkInfoPanel");
        // workInfoPanel->setTopic("/work_info", "hmi_msgs/overlay_text");
    }

    steeringMeter = 
        new hmi_visualization::DoubleValueMeter(0, 0);
    if(steeringMeter)
    {
        steeringMeter->setName("SteeringMeter");
        steeringMeter->setPosition(0, 0);
        manager_->addDisplay(steeringMeter, true);
        // steeringMeter->setTopic("/steering_pub", "hmi_msgs/double_value_meter");
    }

    speedMeter = 
        new hmi_visualization::DoubleValueMeter(0, steeringMeter->height());
    if(speedMeter)
    {
        speedMeter->setName("SpeedMeter");
        speedMeter->setPosition(0, steeringMeter->height());
        manager_->addDisplay(speedMeter, true);
        // speedMeter->setTopic("/speed_pub", "hmi_msgs/double_value_meter");
    }

    imageDisplay = (jsk_rviz_plugins::OverlayImageDisplay*)manager_->createDisplay("jsk_rviz_plugin/OverlayImage", "DisplayImage", true);
    if(imageDisplay)
    {
        imageDisplay->setTopic("/Flir/image_raw", "sensor_msgs/Image");
        imageDisplay->subProp("Topic")->setValue("/Flir/image_raw");

    }
    __setupMenu();

    QTimer *t = new QTimer(this);
    connect(t, &QTimer::timeout, [this]{

        hmi_visualization::DoubleValueMeterParam paramSteering, paramSpeed;
        paramSteering.range_max = 720.0;
        paramSteering.range_min = -720.0;
        paramSteering.value_a = utilities::RosTools::get_instance().getSteering();
        paramSteering.value_b = utilities::RosTools::get_instance().getCtlSteering();
        paramSteering.label = "方向盘";
        steeringMeter->updateData(paramSteering);
        paramSpeed.label = "车速";
        paramSpeed.range_max = 20.0;
        paramSpeed.range_min = 0.0;
        paramSpeed.value_a = utilities::RosTools::get_instance().getSpeed();
        paramSpeed.value_b = utilities::RosTools::get_instance().getCtlSpeed();
        speedMeter->updateData(paramSpeed);
    });
    t->start(20);
}
RvizView::~RvizView()
{
    ROS_INFO_STREAM("release RvizView...");
    if(steeringMeter)
    {
        manager_->getRootDisplayGroup()->takeDisplay(steeringMeter);
        delete steeringMeter;
    }
    if(speedMeter)
    {
        manager_->getRootDisplayGroup()->takeDisplay(speedMeter);
        delete speedMeter;
    }
    if(imageDisplay)
    {
        manager_->getRootDisplayGroup()->takeDisplay(imageDisplay);
        delete imageDisplay;
    }
    if(moduleStatusInfoPanel)
    {
        manager_->getRootDisplayGroup()->takeDisplay(moduleStatusInfoPanel);
        delete moduleStatusInfoPanel;
    }
    if(workInfoPanel)
    {
        manager_->getRootDisplayGroup()->takeDisplay(workInfoPanel);
        delete workInfoPanel;
    }
    // 在这里销毁 manager_ 会导致崩溃
    if (manager_ != nullptr)
    {
        manager_->save(config_);
        manager_->deleteLater();
        manager_ = nullptr;
    }
    if (render_panel_ != nullptr)
    {
        render_panel_->deleteLater();
        render_panel_ = nullptr;
    }

    // 程序退出是保存配置文件，不考虑异常情况
    rviz::YamlConfigWriter writer;
    // QFile file(config_file_);
    // file.remove();
    QFile::remove(config_file_);
    writer.writeFile(config_, config_file_);

    if (writer.error())
    {
        printf("%s", qPrintable(writer.errorMessage()));
    }
}

void RvizView::resizeEvent(QResizeEvent *e)
{
    int overlay_height = 200;
    int overlay_width = 200;
    steeringMeter->setPosition(0, 0);
    speedMeter->setPosition(0, steeringMeter->height());

    imageDisplay->subProp("width")->setValue(render_panel_->width() / 3);
    imageDisplay->subProp("height")->setValue(render_panel_->height() / 3);

    imageDisplay->setPosition(render_panel_->width() - imageDisplay->subProp("width")->getValue().toInt(), 
                              render_panel_->height() - imageDisplay->subProp("height")->getValue().toInt() - overlay_height);
    moduleStatusInfoPanel->movePosition(0,
                                        render_panel_->height() - overlay_height);

    // moduleStatusInfoPanel->setHeight(overlay_height);
    // moduleStatusInfoPanel->setWidth(render_panel_->width() / 2 - 5);
    // moduleStatusInfoPanel->setDimensions(overlay_height, render_panel_->width() / 2 - 5);

    // workInfoPanel->movePosition(render_panel_->width() / 2 + 5,
                                // render_panel_->height() - overlay_height);
    // workInfoPanel->setHeight(overlay_height);
    // workInfoPanel->setWidth(render_panel_->width() / 2 - 5);
}

void RvizView::__setupMenu()
{
    menu_ = new QMenu(this);
    QAction *act = nullptr;
    __addAction(menu_, "Displays", std::bind(&RvizView::__showDisplayPanel, this));
    act = __addAction(menu_, "ShowGrid", [this](bool) { grid_->setEnabled(!grid_->isEnabled()); }, true);
    act->setChecked(grid_->isEnabled());
    connect(grid_, &rviz::Display::changed, [act, this] { act->setChecked(grid_->isEnabled()); });

    __addAction(menu_, "AddTools", std::bind(&RvizView::__addTools, this), false);

    tools_act_group_ = new QActionGroup(menu_);
    tools_act_group_->setExclusive(true);
    connect(tools_act_group_, &QActionGroup::triggered, [this](QAction *act) {
        rviz::ToolManager *tool_manager = manager_->getToolManager();
        if (!tool_manager)
            return;
        qDebug() << "set tool: " << act->text() << act->objectName();
        tool_manager->setCurrentTool(tool_manager->getTool(act->objectName().toInt()));
    });
    menu_->addSection("Tools");

    rviz::ToolManager *tool_manager = manager_->getToolManager();
    tool_manager->removeAll();
    tool_manager->initialize();
    __updateToolGroup();
    if (!tools_act_group_->actions().empty())
        tools_act_group_->actions().at(0)->setChecked(true);
}

void RvizView::__updateToolGroup()
{
    QList<QAction *> actList = tools_act_group_->actions();
    foreach (QAction *act, actList)
    {
        menu_->removeAction(act);
        tools_act_group_->removeAction(act);
        delete act;
    }

    rviz::ToolManager *tool_manager = manager_->getToolManager();
    QStringList toolList = tool_manager->getToolClasses();
    for (int i = 0; i < toolList.size(); i++)
    {
        QAction *act = new QAction(toolList[i]);
        act->setObjectName(QString("%0").arg(i));
        act->setCheckable(true);
        tools_act_group_->addAction(act);
        menu_->addAction(act);
    }
}

QString RvizView::convertType(QVariant value)
{
    // if(value.)
}

void RvizView::logoutModelData(rviz::Property *p)
{
    for (int i = 0; i < p->numChildren(); i++)
    {
        QString data;
        for (int j = 0; j < 2; j++)
            data += p->getViewData(j, i).toString();
        qDebug() << data;
        logoutModelData(p->childAt(i));
    }
}

void RvizView::__showDisplayPanel()
{
    rviz::DisplaysPanel *panel = new rviz::DisplaysPanel();
    panel->initialize(manager_);
    panel->load(config_);
    panel->setAttribute(Qt::WA_DeleteOnClose, true);
    panel->show();
}

void RvizView::readChangedData(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles)
{
    qDebug() << "data is changed" << topLeft << bottomRight << roles;
}

QAction *RvizView::__addAction(QMenu *menu, const QString name, std::function<void(bool)> cb, bool checkable)
{
    QAction *act = new QAction(name);
    act->setCheckable(checkable);
    connect(act, &QAction::triggered, this, cb);
    menu->addAction(act);
    return act;
}

void RvizView::__addTools()
{

    QString class_id;
    QStringList empty;
    rviz::ToolManager *tool_man = manager_->getToolManager();

    rviz::NewObjectDialog *dialog = new rviz::NewObjectDialog(tool_man->getFactory(),
                                                              "Tool",
                                                              empty,
                                                              tool_man->getToolClasses(),
                                                              &class_id);
    manager_->stopUpdate();
    if (dialog->exec() == QDialog::Accepted)
    {
        tool_man->addTool(class_id);
        __updateToolGroup();
    }
    manager_->startUpdate();
    activateWindow(); // Force keyboard focus back on main window.
}

bool RvizView::eventFilter(QObject *obj, QEvent *e)
{
    QMouseEvent *me = nullptr;
    switch (e->type())
    {
    case QEvent::MouseButtonRelease:
        me = static_cast<QMouseEvent *>(e);
        if (me->button() == Qt::MouseButton::RightButton)
        {
            if (is_show_menu_)
            {
                menu_->show();
                menu_->move(me->globalPos());
            }
            return is_show_menu_;
        }
        is_show_menu_ = false;
        break;
    case QEvent::MouseButtonPress:
        is_show_menu_ = true;
        break;
    case QEvent::MouseMove:
        is_show_menu_ = false;
        break;
    }

    return false;
}