#include "utilities.h"
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "cfgfilehelper.h"

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

std::cout << "app dir: " << mDir << std::endl;

    // 创建配置文件目录
    std::vector<std::string> dirs = {
        CfgFileHelper::getDataRecCfgFile(),
        CfgFileHelper::getRvizCfgFile(),
        CfgFileHelper::getTopicWatchTemplateFlie(),
        CfgFileHelper::getScriptFileDir() + "/",
        CfgFileHelper::getModelCfgDir() + "/",
        CfgFileHelper::getModelCfgFile(),
        CfgFileHelper::getVehicleCtlCfgFile(),
    };
    for(auto itor = dirs.begin(); itor != dirs.end(); itor++)
    {
        std::string fileDir = *itor;
        int cut = fileDir.find_last_of('/');
        std::string dir = fileDir.substr(0, cut);
        utilities::APathHelper::createDir(dir);
    }
    
}

int APathHelper::createDir(std::string n)
{
    std::istringstream ss;
    if(n.at(0) == '~')
    {
        std::string home = std::string(getenv("HOME"));
        ss.str(home + n.substr(1, n.size() - 1));
    }
    else
    {
        ss.str(n);
    }
    
    std::string p = "";
    std::string path = "";
    while (std::getline(ss, p, '/'))
    {
        path += p + "/";
        if (access(path.c_str(), NULL) != 0)
        {
            if (mkdir(path.c_str(), 0777) == -1)
            {
                std::cout << "Create Path <" << n << "> Failed!" << std::endl;
                return -1;
            }
        }
    }

    return 0;
}

std::string APathHelper::getHome()
{
    return std::string(getenv("HOME"));
}

}