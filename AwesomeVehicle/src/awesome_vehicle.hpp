#pragma once

#include <iostream>

namespace awe
{
// 初始化
void init();
// 事件循环
void spin();
// 单次事件循环
void spinOnce();
// 判断是否成功
bool ok();



class GlobalCtrlParams
{
public:
    typedef enum {
        STOPPED = 0,
        WORKING = 1,
    } WorkStatus;

public:
    ~GlobalCtrlParams(){}
    GlobalCtrlParams(const GlobalCtrlParams&) = delete;
    GlobalCtrlParams& operator=(const GlobalCtrlParams&)=delete;
    static GlobalCtrlParams& instance(){
        static GlobalCtrlParams ins;
        return ins;
    }

    inline void setWorkStatus(const WorkStatus &status) { __mWorkStatus = status; }
    inline WorkStatus getWorkStatus() { return __mWorkStatus; }

private:
    GlobalCtrlParams(){}
    WorkStatus __mWorkStatus;

};


} // namespace awe
