#include "modelconfigwidget.h"
#include "common_widget/edittabwidget.h"

ModelConfigWidget::ModelConfigWidget(QWidget *parent) : QWidget(parent)
  , mTableWidget(new EditTabWidget(this))
{

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(mTableWidget);

    mTableWidget->setMovable(true);
    mTableWidget->setTabsClosable(true);

    mTableWidget->addTab(new QWidget(this), "Test01");
    mTableWidget->addTab(new QWidget(this), "Test02");
    mTableWidget->addTab(new QWidget(this), "Test03");


}
