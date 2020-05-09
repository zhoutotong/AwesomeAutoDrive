#ifndef DATAVIEWER_H
#define DATAVIEWER_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QTextEdit>

class DataViewer : public QWidget
{
    Q_OBJECT
public:
    explicit DataViewer(QWidget *parent = nullptr);

private:

signals:

};

#endif // DATAVIEWER_H
