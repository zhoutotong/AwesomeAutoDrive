#pragma once

#include <iostream>
#include <thread>
#include <string>
#include <map>

#include <QSettings>

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


#include "ros/ros.h"
#include "ros/package.h"

namespace execctl {

class Execable {

public:
    explicit Execable(const std::string &name) : pid(-1), execThread(nullptr), execName(name) {}
    ~Execable(){}

    virtual void start() = 0;
    virtual void reload() = 0;
    virtual void stop() = 0;

protected:
    int pid;
    std::thread *execThread;
    std::string execName;

};

class CmdExecable
{
public:
    explicit CmdExecable(bool closable = true);
    ~CmdExecable();

    void start(const std::string &cmd);
    void reload();
    void stop();

protected:
    pid_t mPid;
    std::string mCmd;
    std::thread *mWaitThread;
    bool mClosable;
};

class NodeWatch : public Execable {

public:
    explicit NodeWatch(const std::string &name);
    ~NodeWatch();

    void start() override;
    void reload() override;
    void stop() override;

private:
    CmdExecable *cmd;

};

class ExecCtl {
public:
    ~ExecCtl();
    ExecCtl(const ExecCtl&)=delete;
    ExecCtl& operator=(const ExecCtl&)=delete;
    static ExecCtl& get_instance(){
        static ExecCtl instance;
        return instance;
    }

public:
    // inline void setRootPath(std::string path) { mRootPath = path; };

    void startAll();
    void stopAll();

    void start(std::string name);
    void reload(std::string name);
    void stop(std::string name);

private:
    ExecCtl();


private:
    const std::string mRootPath;

#define REGISTER_EXEC(exec) execList.insert(std::pair<std::string, Execable *>(exec, new NodeWatch(exec)));
    std::map<std::string, Execable *> execList;

};


}