#include "base_device.hpp"

namespace awe
{

BaseDevice::BaseDevice(const AString &name, const AString &tag, const AString &label, const AString &type) :
    mName(name)
  , mTag(tag)
  , mLabel(label)
  , mType(type)
{

}

BaseDevice::~BaseDevice()
{

}

void BaseDevice::setup()
{
    AWE_INFO << __FUNCTION__ << " in " << __FILE__ << std::endl;
}
void BaseDevice::release()
{
    AWE_INFO << __FUNCTION__ << " in " << __FILE__ << std::endl;
}
void BaseDevice::start()
{
    AWE_INFO << __FUNCTION__ << " in " << __FILE__ << std::endl;
}
void BaseDevice::stop()
{
    AWE_INFO << __FUNCTION__ << " in " << __FILE__ << std::endl;
}
} // namespace awe
