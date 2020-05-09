#ifndef _UTILITIES_H_
#define _UTILITIES_H_
#include <iostream>
#include <list>

namespace utilities
{
template<class T, class NotifyType>
class Notifier
{
public:
    explicit Notifier(){}
    ~Notifier(){}

    virtual void notify(const NotifyType &data) = 0;
};
} // namespace utilities


#endif // _UTILITIES_H_