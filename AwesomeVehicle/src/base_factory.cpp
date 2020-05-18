#include "base_factory.hpp"

namespace awe
{
BaseFactory::BaseFactory(const AString &name, const AString &tag, const AString &id, const AString &type) :
    mName(name)
  , mTag(tag)
  , mId(id)
  , mType(type)
{

}

BaseFactory::~BaseFactory()
{

}

BaseDevice::BaseDevicePtr BaseFactory::produce(const YAML::Node &node) const
{
    AWE_WARN << "Device Factory " << node.as<AString>() << " Is Not Exist!!!" << std::endl;
    return nullptr;
}

} // namespace awe
