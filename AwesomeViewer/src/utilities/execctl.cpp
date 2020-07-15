#include "execctl.h"
#include <signal.h>
#include <QFile>
#include <QDebug>

#include "cfgfilehelper.h"

namespace execctl {

NodeWatch::NodeWatch(const std::string &name) : Execable(name)
  , cmd(new CmdExecable())
{
}
NodeWatch::~NodeWatch()
{
    stop();
    if(cmd)
    {
        delete cmd;
        cmd = nullptr;
    }
}

void NodeWatch::start()
{
    qDebug() << "start thread now: " << QString::fromStdString(execName);
    std::string pyfile = utilities::CfgFileHelper::getScriptFileDir() + execName + ".py";
    std::string c = ("python2 " + pyfile);
    std::cout << ">>> running: " << c << std::endl;
    if (QFile::exists(QString::fromStdString(pyfile)))
        cmd->start(c.c_str());
    else std::cout << "can not find script: " << pyfile << std::endl;
}
void NodeWatch::reload()
{
    stop();
    start();
}
void NodeWatch::stop()
{
    cmd->stop();
}

ExecCtl::ExecCtl() : mRootPath(utilities::CfgFileHelper::getModelCfgDir()){

    const QString modeListTab = "ModuleList";
    const QString NodeListTab = "NodeList";
    const std::string cfgFile = utilities::CfgFileHelper::getModelCfgFile();

    if(utilities::CfgFileHelper::checkFileExist(cfgFile))
    {
        YAML::Node node = YAML::LoadFile(cfgFile);
        std::cout << "---------------------------------------------------------" << std::endl;
        if(node.IsDefined())
        {
            foreach(auto itor, node)
            {
                std::cout << "register: " << itor.first.as<std::string>() << std::endl;
                REGISTER_EXEC(itor.first.as<std::string>());
            }            
        }
        std::cout << "---------------------------------------------------------" << std::endl;        
    }


}

ExecCtl::~ExecCtl(){
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

CmdExecable::CmdExecable(bool closable) : mPid(-1), mCmd(""), mWaitThread(nullptr), mClosable(closable)
{

}
CmdExecable::~CmdExecable()
{
    
}
void CmdExecable::start(const std::string &cmd)
{
    if(mPid > 0 && mClosable) return;
    if(cmd.empty()) return;
    mCmd = cmd;
    mPid = fork();
    if(mPid == 0)
    {
        std::string c = mCmd.substr(0, mCmd.find_first_of(' '));
        std::string params = mCmd.substr(mCmd.find_first_of(' ') + 1, mCmd.size());

        std::vector<std::string> paramList;
        
        std::stringstream ss(params);
        std::string item;
        while(std::getline(ss, item, ' '))
        {
            if(!item.empty()) paramList.push_back(item);
        }

        const char *argv[512];
        argv[0] = c.c_str();

        for(int i = 0; i < paramList.size(); i++)
        {
            argv[i + 1] = paramList.at(i).c_str();
        }
        argv[paramList.size() + 1] = NULL;


        execvpe(c.c_str(), (char*const*)argv, __environ);

        for(int i = 0; i < paramList.size() + 2; i++)
        {
            delete argv[i];
        }
    }
    else
    {
        // 主线程
        mWaitThread = new std::thread([this] {
            int status = 0;
            waitpid(mPid, &status, 0);
        });
    }
    
}
void CmdExecable::reload()
{

}
void CmdExecable::stop()
{
    if(mPid <= 0) return;
    kill(mPid, SIGINT);
    kill(mPid, SIGKILL);
    mPid = -1;
    if(mWaitThread)
    {
        mWaitThread->join();
        delete mWaitThread;
        mWaitThread = nullptr;
    }
}

// /usr/bin/python /usr/bin/x-terminal-emulator
// /usr/bin/gnome-shell
}