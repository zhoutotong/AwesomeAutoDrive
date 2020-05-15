#include "camera.hpp"

namespace awe
{

Camera::Camera(const AString &name, const AString &tag, const AString &label, const AString &type) : 
    Sensor(name, tag, label, type)
{

}
Camera::~Camera()
{

}

}