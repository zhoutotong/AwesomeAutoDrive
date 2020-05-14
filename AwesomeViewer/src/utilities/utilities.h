#ifndef _UTILITIES_H_
#define _UTILITIES_H_
#include <iostream>
#include <list>
#include <vector>
#include <sstream>

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

class APathHelper
{
public:
    APathHelper(){}

    static void init(const char *name);
    static std::string getAppDir(){ return mDir; }
    static std::string getApp() { return mApp; }
private:
    static std::string mDir;
    static std::string mApp;

};


} // namespace utilities


#endif // _UTILITIES_H_