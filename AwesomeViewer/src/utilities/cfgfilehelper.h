#ifndef _CFG_FILE_HELPER_H_
#define _CFG_FILE_HELPER_H_

#include <iostream>
#include <string>
#include <yaml-cpp/yaml.h>

#include "utilities.h"

namespace utilities {
class CfgFileHelper
{
public:
    CfgFileHelper(){}
    ~CfgFileHelper(){}
    inline static std::string getDataRecCfgFile() {return APathHelper::getAppDir() + "/config/datareccfg.yaml"; };
    inline static std::string getRvizCfgFile() { return "~/.config/AwesomeViewer/rviz/awe.rviz"; }
    inline static std::string getTopicWatchTemplateFlie() { return "~/.config/AwesomeViewer/scripts/template.py"; }
    inline static std::string getScriptFileDir() {return "~/.config/AwesomeViewer/scripts/"; }
    inline static std::string getModelCfgDir() { return "~/.config/AwesomeViewer/model_watch/"; }
    inline static std::string getModelCfgFile() { return "~/.config/AwesomeViewer/config/modelwatch.yaml"; }
    static bool checkAndCreateFile(std::string file);
    static bool checkFileExist(std::string file);
    static bool writeYAML2File(const YAML::Node &n, const std::string &file);
};

};





#endif // _CFG_FILE_HELPER_H_
