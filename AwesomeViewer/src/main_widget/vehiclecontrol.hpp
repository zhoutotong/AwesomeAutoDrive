#pragma once
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>

#include "utilities/execctl.h"


#include <yaml-cpp/yaml.h>

class CmdButton : public QPushButton
{
    Q_OBJECT
public:
    CmdButton(const QString &cmd, bool closable = true, QWidget *parent = nullptr) : QPushButton(parent), mExec(new execctl::CmdExecable(closable)), mCmd(cmd){}
    ~CmdButton(){ if(mExec){delete mExec; mExec = nullptr; }}

    inline void run() { mExec->start(mCmd.toStdString()); }
    inline void shutdown() { mExec->stop(); }

private:
    execctl::CmdExecable *mExec;
    QString mCmd;

};

class VehicleControl : public QWidget
{
    Q_OBJECT
public:
    VehicleControl(QWidget *parent = nullptr);
    ~VehicleControl();

private:

public slots:
    void run();
    void check2run();

};