#ifndef _CFG_FILE_HELPER_H_
#define _CFG_FILE_HELPER_H_

#include <iostream>
#include <string>


namespace utilities {
class CfgFileHelper
{
public:
    CfgFileHelper(){}
    ~CfgFileHelper(){}
    inline static std::string getDataRecCfgFile() {return "./datareccfg.yaml"; };
    inline static std::string getRvizCfgFile() { return "./rviz.yaml"; }
    static bool checkAndCreateFile(std::string file);
    static bool checkFileExist(std::string file);
};

};





#endif // _CFG_FILE_HELPER_H_
