#include "vehiclecontrol.hpp"
#include "utilities/cfgfilehelper.h"

VehicleControl::VehicleControl(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    // QPushButton *startBtn = new QPushButton("开始", this);
    // QPushButton *stopBtn = new QPushButton("停止", this);
    // layout->addWidget(startBtn);
    // layout->addWidget(stopBtn);

    // 从配置文件中加载
    YAML::Node root;
    std::string cfgFile = utilities::CfgFileHelper::getVehicleCtlCfgFile();
    if(utilities::CfgFileHelper::checkAndCreateFile(cfgFile))
    {
        root = YAML::LoadFile(cfgFile);
        if(!root["ctl_btns"].IsSequence())
        {
            QMessageBox::warning(this, "Warning", "车辆配置文件异常！");
        }
        else
        {
            for(auto itor = root["ctl_btns"].begin(); itor != root["ctl_btns"].end(); itor++)
            {
                CmdButton *btn = new CmdButton(QString::fromStdString((*itor)["cmd"].as<std::string>()),\
                                              (*itor)["closable"].as<bool>(), this);
                btn->setText(QString::fromStdString((*itor)["text"].as<std::string>()));

                if((*itor)["closable"].as<bool>())
                {
                    // 可退出命令
                    btn->setCheckable(true);
                    connect(btn, &CmdButton::clicked, this, &VehicleControl::check2run);
                }
                else
                {
                    // 单次触发命令
                    btn->setCheckable(false);
                    connect(btn, &CmdButton::clicked, this, &VehicleControl::run);
                }

                layout->addWidget(btn);
                std::cout << "add btn: " << (*itor)["text"] << std::endl;
                
            }
        }
        
    }

    // connect(startBtn, &QPushButton::clicked, this, &VehicleControl::start);
    // connect(stopBtn, &QPushButton::clicked, this, &VehicleControl::stop);

}
VehicleControl::~VehicleControl()
{

}

void VehicleControl::run()
{
    static_cast<CmdButton*>(sender())->run();
}
void VehicleControl::check2run()
{
    CmdButton* btn = static_cast<CmdButton*>(sender());
    if(btn->isChecked())
    {
        btn->run();
    }
    else
    {
        btn->shutdown();
    }
    
}
