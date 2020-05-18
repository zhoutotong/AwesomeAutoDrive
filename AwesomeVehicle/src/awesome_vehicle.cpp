#include "awesome_vehicle.hpp"
#include <unistd.h>
#include <signal.h>
#include "utilities/typedef.hpp"

typedef void(*SysSigCb)();

#define SIG_HANDLER_LIST AMap<int, SysSigCb> sysSigCbs =
#define REG_SIG_HANDLER(num, handler) std::make_pair(num, []handler)


namespace awe
{

SIG_HANDLER_LIST
{
REG_SIG_HANDLER(SIGINT, {
    GlobalCtrlParams::instance().setWorkStatus(GlobalCtrlParams::WorkStatus::STOPPED);
})
};


// 处理系统信号量
void sysSigHandler(int num)
{
    auto handler = sysSigCbs.find(num);
    if(handler != sysSigCbs.end())
    {
        handler->second();
    }
}



// 初始化
void init()
{
    // 设置全局标识，指示开始工作
    GlobalCtrlParams::instance().setWorkStatus(GlobalCtrlParams::WorkStatus::WORKING);

    struct sigaction act;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask, SIGINT); //屏蔽 ctrl + c 信号
    act.sa_handler = sysSigHandler;

    // 注册捕捉
    sigaction(SIGINT, &act, NULL);
    return;
}

// 判断是否成功
bool ok()
{
    if(GlobalCtrlParams::instance().getWorkStatus() == GlobalCtrlParams::WorkStatus::WORKING)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// 事件循环
void spin()
{
    while(ok())
    {
        sleep(1);
    }
    return;
}
// 单次事件循环
void spinOnce()
{
    return;
}
} // namespace awe