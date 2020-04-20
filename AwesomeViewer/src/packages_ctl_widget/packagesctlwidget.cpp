#include "packagesctlwidget.h"

PackagesCtlWidget::PackagesCtlWidget(QWidget *parent) : QWidget(parent)
  , mTableWidget(new QTableWidget(this))
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(mTableWidget);

    mTableWidget->verticalHeader()->setVisible(false);

    const QStringList headerLabels = {"Package", "Command", "Status", "Un/Install"};
    mTableWidget->setColumnCount(headerLabels.size());
    mTableWidget->setHorizontalHeaderLabels(headerLabels);

    __addItem("rs_lidar");
}

void PackagesCtlWidget::__addItem(const QString &package)
{
    mTableWidget->setRowCount(mTableWidget->rowCount() + 1);
    int rowConunt = mTableWidget->rowCount() - 1;
    mTableWidget->setItem(rowConunt, 0, new QTableWidgetItem(package));


    QLabel *statusLabel = new QLabel("Installed", mTableWidget);
    statusLabel->setStyleSheet("background-color:red");

    QPushButton *installBtn = new QPushButton("Install");
    installBtn->setStyleSheet("background-color:green");

    mTableWidget->setCellWidget(rowConunt, 2, statusLabel);
    mTableWidget->setCellWidget(rowConunt, 3, installBtn);
}
