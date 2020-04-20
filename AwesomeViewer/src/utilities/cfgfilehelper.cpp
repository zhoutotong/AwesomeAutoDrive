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

} // namespace utilities
