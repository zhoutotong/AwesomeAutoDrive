#include "base_factory.hpp"

namespace awe
{
BaseFactory::BaseFactory(const AString &name, const AString &tag, const AString &label, const AString &type) :
    mName(name)
  , mTag(tag)
  , mLabel(label)
  , mType(type)
{

}

BaseFactory::~BaseFactory()
{

}

BaseDevice::BaseDeviceUniquePtr BaseFactory::produce(const YAML::Node &node) const
{
    AWE_WARN << "Device Factory " << node.as<AString>() << " Is Not Exist!!!" << std::endl;
    return std::make_unique<BaseDevice>("","","","");
}

} // namespace awe
