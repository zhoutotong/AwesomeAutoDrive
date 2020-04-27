#include "execctl.h"
#include <signal.h>
#include <QFile>
#include <QDebug>

#include "cfgfilehelper.h"

namespace execctl {

NodeWatch::NodeWatch(const std::string &name) : Execable(name)
{
}
NodeWatch::~NodeWatch()
{
    stop();
}

void NodeWatch::start()
{
    // 检查线程是否在执行
    if(execThread)
    {
        execThread->detach();
        delete execThread;
        execThread = nullptr;
    }
    qDebug() << "start thread now: " << QString::fromStdString(execName);
    execThread = new std::thread([this]{
        std::string pyfile = utilities::CfgFileHelper::getModelCfgDir() + execName + ".py";
        qDebug() << ">>> running: " << QString::fromStdString(pyfile);
        if(QFile::exists(QString::fromStdString(pyfile)))
            pid = system(std::string("python " + pyfile).c_str());
        std::cout << _LOCALE_CLASSES_TCC << __LINE__ << "-->" << execName << " NodeWatch thread is Exited!!!" << std::endl;
    });
}
void NodeWatch::reload()
{
    stop();
    start();
}
void NodeWatch::stop()
{
    // 杀死启动的监测进程
    QString cmd = "ps -aux | grep -E \'<scrpit>\' | awk '{print $2}' | xargs kill -9";
    std::string pyfile = utilities::CfgFileHelper::getModelCfgDir() + execName + ".py";
    cmd.replace("<scrpit>", QString::fromStdString(pyfile));

    system(cmd.toStdString().c_str());

    // 检查线程是否在执行
    if(execThread)
    {// 这个线程用来执行监控程序
        execThread->detach();
        delete execThread;
        execThread = nullptr;
    }
}

ExecCtl::ExecCtl() : mRootPath(utilities::CfgFileHelper::getModelCfgDir()){
    std::cout<<"constructor called!"<<std::endl;

    const QString modeListTab = "ModuleList";
    const QString NodeListTab = "NodeList";
    const std::string cfgFile = utilities::CfgFileHelper::getModelCfgFile();

    YAML::Node node = YAML::LoadFile(cfgFile);
    std::cout << "---------------------------------------------------------" << std::endl;

    foreach(auto itor, node)
    {
        std::cout << "register: " << itor.first.as<std::string>() << std::endl;
        REGISTER_EXEC(itor.first.as<std::string>());
    }

    std::cout << "---------------------------------------------------------" << std::endl;
}

ExecCtl::~ExecCtl(){
    std::cout<<"destructor called!"<<std::endl;
    for(auto itor = execList.begin(); itor != execList.end(); itor++)
    {
        delete itor->second;
    }
}

void ExecCtl::startAll()
{
    for(auto itor = execList.begin(); itor != execList.end(); itor++)
    {
        itor->second->start();
    }
}
void ExecCtl::stopAll()
{
    for(auto itor = execList.begin(); itor != execList.end(); itor++)
    {
        itor->second->stop();
    }
}

void ExecCtl::start(std::string name)
{
    auto exec = execList.find(name);
    if(exec == execList.end()) return;
    exec->second->start();
}
void ExecCtl::reload(std::string name)
{
    qDebug() << "reload: " << QString::fromStdString(name);
    auto exec = execList.find(name);
    if(exec == execList.end()) return;
    exec->second->reload();
}
void ExecCtl::stop(std::string name)
{
    auto exec = execList.find(name);
    if(exec == execList.end()) return;
    exec->second->stop();
}


}