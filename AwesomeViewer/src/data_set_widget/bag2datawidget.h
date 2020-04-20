#ifndef BAG2DATAWIDGET_H
#define BAG2DATAWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QListWidget>
#include <QFileInfoList>
#include <QDir>
#include <QLineEdit>

class Bag2DataWidget : public QWidget
{
    Q_OBJECT
public:
    explicit Bag2DataWidget(QWidget *parent = nullptr);

private:
    QListWidget *mDocFileListWidget;
    QLineEdit *mOutputLine;

    QString mCurrentDir;

private slots:
    void openDocument();
    void setOutputDir();
signals:

};

#endif // BAG2DATAWIDGET_H
