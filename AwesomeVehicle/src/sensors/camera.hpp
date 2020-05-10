#pragma once

#include <iostream>

#include "sensor.hpp"

namespace awesomevehicle
{

class Camera : public Sensor
{
public:
    explicit Camera();
    ~Camera();
};


} // namespace awesomevehicle
