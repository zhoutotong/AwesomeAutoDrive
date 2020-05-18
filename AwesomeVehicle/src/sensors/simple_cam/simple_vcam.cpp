#include "simple_vcam.hpp"
#include "awe.hpp"

namespace awe
{

SimpleVCam::SimpleVCam(const AString &name, const AString &tag, const AString &id, const AString &type) : 
    Camera(name, tag, id, type)
{
    awe::AWE_INFO << __FUNCTION__ << " in " << __FILE__ << std::endl;
}

SimpleVCam::~SimpleVCam()
{
    awe::AWE_INFO << __FUNCTION__ << " in " << __FILE__ << std::endl;
}

void SimpleVCam::setup()
{
    awe::AWE_INFO << __FUNCTION__ << " in " << __FILE__ << std::endl;
}
void SimpleVCam::release()
{
    awe::AWE_INFO << __FUNCTION__ << " in " << __FILE__ << std::endl;
}
void SimpleVCam::start()
{
    awe::AWE_INFO << __FUNCTION__ << " in " << __FILE__ << std::endl;
}
void SimpleVCam::stop()
{
    awe::AWE_INFO << __FUNCTION__ << " in " << __FILE__ << std::endl;
}
} // namespace awe
