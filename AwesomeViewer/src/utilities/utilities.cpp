#include "utilities.h"
#include <unistd.h>


namespace utilities
{
std::string APathHelper::mDir;
std::string APathHelper::mApp;
void APathHelper::init(const char *name)
{
    char link[1024];

    // 直接检查，查看是否存在
    int len = readlink(name, link, sizeof(link) - 1);

    // 如果不存在，则添加环境变量再查找
    if(-1 == len)
    {
        std::vector<std::string> paths;
        std::stringstream ss;
        ss << secure_getenv("PATH");
        for(std::string dir; std::getline(ss, dir, ':');)
        {
            len = readlink((dir + "/" + std::string(name)).c_str(), link, sizeof(link) - 1);
            if(len != -1)
            {
                break;
            }
        }
    }

    if(len != -1)
    {
        link[len] = '\0';
        std::string fullname(link);
        int cutpos = fullname.find_last_of('/');
        mDir = fullname.substr(0, cutpos);
        mApp = fullname.substr(cutpos + 1, fullname.size() - cutpos);
    }
    else
    {
        // 如果仍然不存在，就认为输入的已经是源文件本体了
        std::string curdir(get_current_dir_name());
        std::string curapp(name);
        std::string::size_type cutpos = curapp.find_last_of('/');
        mDir = curdir + "/" + curapp.substr(0, cutpos);
        mApp = curapp.substr(cutpos + 1, curapp.size() - cutpos);
    }
    
}

}