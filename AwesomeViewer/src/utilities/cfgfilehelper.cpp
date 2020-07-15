#include "cfgfilehelper.h"
#include <unistd.h>

namespace utilities {
bool CfgFileHelper::checkAndCreateFile(std::string file)
{
    if(access(file.c_str(), F_OK))
    {
        FILE * fd = fopen(file.c_str(), "w+");
        if(!fd)
        {
            return false;
        }
        fclose(fd);
    }
    return true;
}

bool CfgFileHelper::checkFileExist(std::string file)
{
    if(access(file.c_str(), F_OK))
    {
        return false;
    }
    return true;
}

bool CfgFileHelper::writeYAML2File(const YAML::Node &n, const std::string &file)
{
    std::stringstream ss;
    ss << n;
    std::cout << ss.str() << std::endl;
    std::cout << file << std::endl;
    FILE *fd = fopen(file.c_str(), "w");
    std::cout << fd << std::endl;
    fwrite(ss.str().c_str(), 1, ss.str().size(), fd);
    fclose(fd);
}

} // namespace utilities
