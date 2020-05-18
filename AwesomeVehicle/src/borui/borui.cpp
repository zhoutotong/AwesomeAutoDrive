#include "borui.hpp"

namespace awe
{
BoRui::BoRui(const AString &name, const AString &tag, const AString &id, const AString &type) :
    Vehicle(name, tag, id, type)
{

}
BoRui::~BoRui()
{
    AWE_INFO << "release borui obj..." << std::endl;
}

/**
 * brief: 初始化车辆
 **/
void BoRui::setup()
{
    AWE_INFO << __FUNCTION__ << " In " << __FILE__ << std::endl;
}
/**
 * brief: 释放资源
 **/
void BoRui::release()
{
    AWE_INFO << __FUNCTION__ << " In " << __FILE__ << std::endl;
}

/**
 * brief: 启动车辆
 **/
void BoRui::start()
{
    AWE_INFO << __FUNCTION__ << " In " << __FILE__ << std::endl;
}

/**
 * brief: 停止运行
 **/
void BoRui::stop()
{
    AWE_INFO << __FUNCTION__ << " In " << __FILE__ << std::endl;
}


} // namespace awe
