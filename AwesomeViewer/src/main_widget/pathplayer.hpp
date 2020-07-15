#pragma once

#include <QWidget>
#include <QListWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QTextLine>
#include <QButtonGroup>

class PathPlayer : public QWidget
{
    Q_OBJECT

private:
    using PathItem = QVector<QWidget*>;
public:
    explicit PathPlayer(QWidget *parent = nullptr);
    ~PathPlayer();
private:
    QTableWidget *mPathListWidget;
    QButtonGroup *mPathSelectGroup;

    void createPathItem(PathItem &item);
    void addItem(const PathItem &item);

public slots:
    void changePathStatus();
};