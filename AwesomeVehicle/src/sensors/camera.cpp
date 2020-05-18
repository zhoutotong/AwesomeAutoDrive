#include "camera.hpp"

namespace awe
{

Camera::Camera(const AString &name, const AString &tag, const AString &id, const AString &type) : 
    Sensor(name, tag, id, type)
{

}
Camera::~Camera()
{

}

}