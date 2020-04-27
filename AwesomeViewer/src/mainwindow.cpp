#include "mainwindow.h"
#include "config_widget/configurewidget.h"
// #include "packages_ctl_widget/packagesctlwidget.h"
// #include "ros_tools_widget/rostoolswidget.h"
#include "data_set_widget/datasetwidget.h"
#include "main_widget/mainwidget.h"
#include "statewidget.h"
#include "utilities/execctl.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *w = new QWidget(this);
    QVBoxLayout *l = new QVBoxLayout(w);
    setCentralWidget(w);

    setMinimumSize(960, 640);

    QTabWidget *tabWidget = new QTabWidget(w);
    l->addWidget(tabWidget);

    tabWidget->setTabPosition(QTabWidget::West);

    tabWidget->addTab(new mainwidget::MainWidget(this), "Main");
    tabWidget->addTab(new StateWidget(this), "Detail");
    // tabWidget->addTab(new RosToolsWidget(this), "RosTools");
    // tabWidget->addTab(new DataSetWidget(this), "DataSet");
    tabWidget->addTab(new ConfigureWidget(this), "Configure");
    // tabWidget->addTab(new PackagesCtlWidget(this), "Packages");

    // tabWidget->setCurrentIndex(3);

    // statusBar()->showMessage("null");

}

MainWindow::~MainWindow()
{
    execctl::ExecCtl::get_instance().stopAll();
}

