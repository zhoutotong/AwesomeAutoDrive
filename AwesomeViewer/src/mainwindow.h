#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QStatusBar>
#include <QApplication>
#include "rvizview/visualizer_app.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(rviz::VisualizerApp *vapp, QWidget *parent = nullptr);
    ~MainWindow();

private:
    const rviz::VisualizerApp *mVapp;
protected:
    void closeEvent( QCloseEvent* event );
};
#endif // MAINWINDOW_H
