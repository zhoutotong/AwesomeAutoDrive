#pragma once

#include <iostream>

namespace awe
{

class Destination
{
public:
    Destination(){}
    ~Destination(){}
};

class CanDestination : public Destination
{

};

class Communicator
{

public:
    Communicator();
    ~Communicator();

    virtual void setup();
    virtual void release();

    virtual void sendTo(Destination dest, void *data, uint32_t len);

};
} // namespace awe
