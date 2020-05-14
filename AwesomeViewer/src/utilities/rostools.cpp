#include "rostools.h"
#include <QDebug>

#include <mutex>
#include <exception>

double gSpeed;
double gSteering;
double gCtlSpeed;
double gCtlSteering;

namespace utilities
{

RosTools::RosTools() : __n(nullptr), __workThread(nullptr), __isWorking(false)
{

}

void RosTools::initRosTools(int argc, char *argv[])
{
    std::cout << std::this_thread::get_id() << std::endl;

    ros::init(argc, argv, "Awesome");
    // 启动内部话题订阅
    __workThread = new std::thread([this, &argc, &argv]{
        __isWorking = true;
        ros::NodeHandle n;
        ros::Subscriber subChassis = n.subscribe<nox_msgs::Chassis>("/chassis", 10, std::bind(&RosTools::chassisCb, this, std::placeholders::_1));
        ros::Subscriber subDrivingCommand = n.subscribe<nox_msgs::DrivingCommand>("/driving_command", 10, std::bind(&RosTools::drivingCommandCb, this, std::placeholders::_1));
        ros::Rate loop(50.0);

        while(__isWorking)
        {
            try{
            ros::spinOnce();
            loop.sleep();
 }catch(std::exception &e){
    std::cout << "ros run exception: " << e.what() << std::endl;
}           
        }


        std::cout << "Ros Tools Thread Is Exist!!!" << std::endl;
    });

}

double RosTools::getSpeed()
{
    return gSpeed;
}
double RosTools::getSteering()
{
    return gSteering;
}

double RosTools::getCtlSpeed()
{
    return gCtlSpeed;
}
double RosTools::getCtlSteering()
{
    return gCtlSteering;
}

void RosTools::subscribeTopics()
{
    // 订阅底盘信息话题

    // 订阅控制信息

}

void RosTools::chassisCb(const nox_msgs::Chassis::ConstPtr &msg)
{
    // gChassis = nox_msgs::Chassis(*msg);
    gSpeed = msg->speed;
    gSteering = msg->steering;
}

void RosTools::drivingCommandCb(const nox_msgs::DrivingCommand::ConstPtr &msg)
{
    // gDrivingCommand = nox_msgs::DrivingCommand(*msg);
    gCtlSteering = msg->target_steering;
    gCtlSpeed = msg->target_speed;
}

std::map<std::string, std::string> RosTools::getTopicList()
{
    ros::master::V_TopicInfo topics;
    std::map<std::string, std::string> ts;
    ros::master::getTopics(topics);
    for(auto itor = topics.begin(); itor != topics.end(); itor++)
    {
        ts.insert(std::pair<std::string, std::string>(itor->name, itor->datatype));
    }
    return ts;
}


QString findTag(const QString &bodyIn, const YAML::Node tagMap)
{
    // std::cout << "process tag: " << temp.toStdString() << std::endl;
    // std::cout << "tagList: " << tagList << std::endl;
    QString t = bodyIn;
    // std::cout << "body: " << t.toStdString() << std::endl;

    // 查找 tag 头
    QRegExp headExp("<%{1}");
    int headStart = headExp.indexIn(t);
    if(headStart == -1) return "";
    int headLength = headExp.matchedLength();

    // 查找 tag 尾
    QRegExp tailExp(("%>{1}"));
    int tailStart = tailExp.indexIn(t, headStart + headLength);
    if(tailStart == -1) return "";
    int tailLength = tailExp.matchedLength();

    // 提取 tag 内容
    int bodyStart = headStart + headLength;
    int bodyLength = tailStart - headStart - headLength;
    QString body = t.mid(bodyStart, bodyLength);

    if(tagMap[body.toStdString()].IsDefined())
    {
        t.replace("<%" + body + "%>", QString::fromStdString(tagMap[body.toStdString()].as<std::string>()));
    }
    else
    {
        t.remove("<%" + body + "%>");
        return "";
    }

    return t;
}

QString replaceTag(const QString &bodyIn, const YAML::Node tagMap)
{
    QString res;
    QString r = findTag(bodyIn, tagMap);
    res = r;
    while(!r.isEmpty())
    {
        res = r;
        r = findTag(r, tagMap);
    }
    return res;
}

bool findTemplate(QString &bodyin, YAML::Node &templateMap)
{
    QString &t = bodyin;

    // 查找模板标签
    QRegExp headExp("[<]{1}[0-9,a-z,A-Z,_]{1,}[>]{1}");
    int headStart = headExp.indexIn(t, 0);
    if(headStart == -1)
    {
        // 不存在则返回
        return false;
    }
    int headLength = headExp.matchedLength();

    // 提取模板标签
    QString tab = t.mid(headStart + 1, headLength - 2);

    // 查找模板结尾
    QRegExp tailExp("</{1}" + tab + "{1}[>]{1}");
    int tailStart = tailExp.indexIn(t, headStart + headLength + 1);
    if(tailStart == -1) return false; // 未找到就返回，此处代表模板异常
    int tailLength = tailExp.matchedLength();

    // 提取模板内容
    int bodyStart = headStart + headLength;
    int bodyLength = tailStart - headLength - headStart;
    QString body = t.mid(bodyStart, bodyLength);

    templateMap[tab.toStdString()] = body.toStdString();

    // 将处理完成的 template 放入父模板
    t.remove(headStart, headLength + bodyLength + tailLength);

    return true;
}


void RosTools::generateTopicWatch(const std::string &node_name, const std::string &node, const std::string &output)
{
    std::cout << node << std::endl;
    // 检查配置文件是不是存在，如果不存在就返回
    if(!CfgFileHelper::checkFileExist(node))
    {
        std::cout << "配置文件不存在" << std::endl;
        return;
    }
    // 从配置文件中加载数据
    YAML::Node root = YAML::LoadFile(node);
    std::cout << root << std::endl;

    // 载入模板
    std::string templateFile = CfgFileHelper::getTopicWatchTemplateFlie();
    std::ifstream fin(templateFile);
    std::stringstream ss;
    ss << fin.rdbuf();
    fin.close();
    QString t = QString::fromStdString(ss.str());

    YAML::Node templates = YAML::Load("{}");
    YAML::Node items = YAML::Load("{}");
    // 查找全部子模板
    while(findTemplate(t, templates));

    // 提取模板
    QString initDictTemp = QString::fromStdString(templates["init_dict_topic"].as<std::string>());
    QString initDictParamTemp = QString::fromStdString(templates["init_dict_param"].as<std::string>());
    QString subTopicTemp = QString::fromStdString(templates["sub_topic"].as<std::string>());
    QString hzCheckTemp = QString::fromStdString(templates["hz_check"].as<std::string>());
    QString callbackTemp = QString::fromStdString(templates["call_back"].as<std::string>());
    QString callbackCheckParamTemp = QString::fromStdString(templates["callback_check_param"].as<std::string>());
    QString hzStateCheckTemp = QString::fromStdString(templates["hz_state_check"].as<std::string>());
    QString loadparamInfoTemp = QString::fromStdString(templates["load_param_info"].as<std::string>());
    QString importPkgTemp = QString::fromStdString(templates["import_pkg_list"].as<std::string>());

    QString initDictStr;
    QString subTopicStr;
    QString hzCheckStr;
    QString callbackStr;
    QString hzStateCheckStr;
    QString loadparamInfoStr;
    QString importPkgStr;
    for(auto itor = root.begin(); itor != root.end(); itor++)
    {
        YAML::Node n = YAML::Load("{}");
        n["topic"] = itor->first;
        // 查找type
        QString topT = QString::fromStdString(itor->second["type"].as<std::string>());
        QStringList topTL = topT.split("/");
        topT = topTL.at(topTL.size() - 1);
        QString pkgName = topTL.at(0);
        std::cout << topT.toStdString() << std::endl;
        // 生成 topic label
        QString topL = QString::fromStdString(itor->second["type"].as<std::string>());
        topL.replace('/', '_');

        n["topic_type"] = topT.toStdString();
        n["topic_label"] = topL.toStdString();
        n["hz_min"] = itor->second["hz_min"];
        n["hz_max"] = itor->second["hz_max"];
        n["pkg_name"] = pkgName.toStdString();
        initDictStr += replaceTag(initDictTemp, n);
        subTopicStr += replaceTag(subTopicTemp, n);
        callbackStr += replaceTag(callbackTemp, n);
        hzCheckStr += replaceTag(hzCheckTemp, n);
        hzStateCheckStr += replaceTag(hzStateCheckTemp, n);
        importPkgStr += replaceTag(importPkgTemp, n);
        // 遍历处理 param
        for(auto paramItor = itor->second["params"].begin(); paramItor != itor->second["params"].end(); paramItor++)
        {
            n["param"] = paramItor->first;
            n["param_min"] = paramItor->second["min"];
            n["param_max"] = paramItor->second["max"];
            initDictStr += replaceTag(initDictParamTemp, n);
            callbackStr += replaceTag(callbackCheckParamTemp, n);
            loadparamInfoStr += replaceTag(loadparamInfoTemp, n);
        }
    }

    items["node_name"] = node_name + "_node";
    items["init_dict_topic"] = initDictStr.toStdString();
    items["sub_topic"] = subTopicStr.toStdString();
    items["hz_check"] = hzCheckStr.toStdString();
    items["call_back"] = callbackStr.toStdString();
    items["hz_state_check"] = hzStateCheckStr.toStdString();
    items["load_param_info"] = loadparamInfoStr.toStdString();
    items["import_pkg_list"] = importPkgStr.toStdString();

    // 生成监测脚本
    QString script = replaceTag(t, items);

    FILE *fd = fopen(output.c_str(), "w");
    if(!fd) return;
    fwrite(script.toStdString().c_str(), 1, script.size(), fd);
    fclose(fd);
}

} // namespace utilities
