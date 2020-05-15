#include "daheng.hpp"
#include "awe.hpp"

namespace awe
{

DaHeng::DaHeng(const AString &name, const AString &tag, const AString &label, const AString &type) : 
    Camera(name, tag, label, type)
{
    AWE_INFO << __FUNCTION__ << " in " << __FILE__ << std::endl;
}

DaHeng::~DaHeng()
{
    AWE_INFO << __FUNCTION__ << " in " << __FILE__ << std::endl;
}

void DaHeng::setup()
{
    AWE_INFO << __FUNCTION__ << " in " << __FILE__ << std::endl;
}
void DaHeng::release()
{
    AWE_INFO << __FUNCTION__ << " in " << __FILE__ << std::endl;
}
void DaHeng::start()
{
    AWE_INFO << __FUNCTION__ << " in " << __FILE__ << std::endl;
}
void DaHeng::stop()
{
    AWE_INFO << __FUNCTION__ << " in " << __FILE__ << std::endl;
}
}