#include "datareccfg.h"
#include "utilities/cfgfilehelper.h"

#include <QMessageBox>

DataRecCfg::DataRecCfg(QWidget *parent) : QWidget(parent)
  , mTableWidget(nullptr)
  , mCfgFile(QString::fromStdString(utilities::CfgFileHelper::getDataRecCfgFile()))
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    setLayout(layout);

    mTableWidget = new QTableWidget(this);
    layout->addWidget(mTableWidget);

    // 设置表头
    const QStringList tableHeader = {"名称", "话题列表", "选项"};
    mTableWidget->setColumnCount(tableHeader.size());
    mTableWidget->setHorizontalHeaderLabels(tableHeader);

    // 设置表头宽度规则
    mTableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    // 初始化添加按钮
    QPushButton *addBtn = new QPushButton("添加", this);
    addBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    layout->addWidget(addBtn, Qt::AlignRight);
    connect(addBtn, &QPushButton::clicked, std::bind(&DataRecCfg::addItem, this, "", ""));

    // 检查配置文件是否存在
    if(!utilities::CfgFileHelper::checkFileExist(utilities::CfgFileHelper::getDataRecCfgFile()))
    {
        // 如果不存在则新建，并初始化内容
        fclose(fopen(utilities::CfgFileHelper::getDataRecCfgFile().c_str(), "w+"));
        YAML::Node n = YAML::LoadFile(utilities::CfgFileHelper::getDataRecCfgFile());
        n = YAML::Load("{}");
        std::ofstream fout(utilities::CfgFileHelper::getDataRecCfgFile());
        fout << n;
    }
    loadFromCfgFile(mCfgFile);
}

DataRecCfg::~DataRecCfg()
{
    // 释放表格资源
    for(int i = 0; i < mTableWidget->rowCount(); i++)
    {
        delete mTableWidget->cellWidget(i, 0);
        delete mTableWidget->cellWidget(i, 1);
        delete mTableWidget->cellWidget(i, 2);
    }
}

void DataRecCfg::loadFromCfgFile(const QString &cfg)
{
    // 加载配置文件，如果配置文件异常则使用空配置文件
    YAML::Node cfgFile;
    try
    {
        cfgFile = YAML::LoadFile(mCfgFile.toStdString());
    }
    catch (YAML::Exception &e)
    {
        std::cout << e.what() << std::endl;
        cfgFile = YAML::Load("{}");
    }

    if(!cfgFile.IsMap())
    {
        // TODO: cfg file is not map
        QMessageBox::critical(this, "Error", "配置文件异常，请清空配置文件");
        return;
    }

    for(auto itor = cfgFile.begin(); itor != cfgFile.end(); itor++)
    {
        QString topics;
        std::string name = itor->first.as<std::string>();
        for(auto it = cfgFile[itor->first.as<std::string>()].begin();
                it != cfgFile[itor->first.as<std::string>()].end(); it++)
        {
            QString t = QString::fromStdString(it->as<std::string>());
            topics += (topics.size() == 0) ? t : (";" + t);
        }
        addItem(QString::fromStdString(name), topics);
    }
}

void DataRecCfg::addItem(const QString &name, const QString &topics)
{
    // 初始化命名控件
    QLineEdit *nameEdit = new QLineEdit(name);
    nameEdit->setPlaceholderText("请勿重复");
    // 初始化话题列表框
    QLineEdit *topicsEdit = new QLineEdit(topics);
    topicsEdit->setPlaceholderText("多个话题以\";\"隔开");
    // 初始化按钮控件
    QWidget *ctlWidget = new QWidget();
    QHBoxLayout* ctlLayout = new QHBoxLayout(ctlWidget);
    ctlLayout->setMargin(0);
    ctlLayout->setAlignment(Qt::AlignCenter);
    QPushButton* updateBtn = new QPushButton("更新", ctlWidget);
    QPushButton* removeBtn = new QPushButton("删除", ctlWidget);
    ctlLayout->addWidget(updateBtn);
    ctlLayout->addWidget(removeBtn);

    // 连接功能槽函数
    connect(updateBtn, &QPushButton::clicked, std::bind(&DataRecCfg::updateItem, this, nameEdit));
    connect(removeBtn, &QPushButton::clicked, std::bind(&DataRecCfg::removeItem, this, nameEdit));

    int cCnt = mTableWidget->rowCount();
    mTableWidget->setRowCount(cCnt + 1);
    mTableWidget->setCellWidget(cCnt, 0, nameEdit);
    mTableWidget->setCellWidget(cCnt, 1, topicsEdit);
    mTableWidget->setCellWidget(cCnt, 2, ctlWidget);
}

void DataRecCfg::removeItem(QWidget * index)
{
    int ind = -1;
    // 查找要移除的行
    for(int i = 0; i < mTableWidget->rowCount(); i++)
    {
        if(index == mTableWidget->cellWidget(i, 0))
        {
            ind = i;
            break;
        }
    }

    // 如果查找到则移除该行
    if(ind != -1)
    {
        QLineEdit* nameLine = static_cast<QLineEdit*>(mTableWidget->cellWidget(ind, 0));
        QLineEdit* topicLine = static_cast<QLineEdit*>(mTableWidget->cellWidget(ind, 1));

        std::string nameStr = nameLine->text().toStdString();
        QString topicStr = topicLine->text();
        QStringList topicList = topicStr.split(';');

        // 加载配置文件，如果配置文件异常则使用空配置文件
        YAML::Node cfgFile;
        try
        {
            cfgFile = YAML::LoadFile(mCfgFile.toStdString());
        }
        catch (YAML::Exception &e)
        {
            std::cout << e.what() << std::endl;
            cfgFile = YAML::Load("{}");
        }

        if(cfgFile.IsNull())
        {
            cfgFile = YAML::Load("[]");
        }

        // 查找任务列表，如果存在就删除
        if(cfgFile[nameStr].IsDefined())
        {
            cfgFile.remove(nameStr);
        }
        // 保存至文件
        std::ofstream fout(mCfgFile.toStdString());
        fout << cfgFile;

        // 从界面中删除
        delete mTableWidget->cellWidget(ind, 0);
        delete mTableWidget->cellWidget(ind, 1);
        delete mTableWidget->cellWidget(ind, 2);
        mTableWidget->removeRow(ind);
    }
}

void DataRecCfg::updateItem(QWidget * index)
{
    int ind = -1;
    // 查找要移除的行
    for(int i = 0; i < mTableWidget->rowCount(); i++)
    {
        if(index == mTableWidget->cellWidget(i, 0))
        {
            ind = i;
            break;
        }
    }

    // 如果查找到则更新
    if(ind != -1)
    {
        QLineEdit* nameLine = static_cast<QLineEdit*>(mTableWidget->cellWidget(ind, 0));
        QLineEdit* topicLine = static_cast<QLineEdit*>(mTableWidget->cellWidget(ind, 1));

        std::string nameStr = nameLine->text().toStdString();
        QString topicStr = topicLine->text();
        QStringList topicList = topicStr.split(';');

        // 加载配置文件，如果配置文件异常则使用空配置文件
        YAML::Node cfgFile;
        try
        {
            cfgFile = YAML::LoadFile(mCfgFile.toStdString());
        }
        catch (YAML::Exception &e)
        {
            std::cout << e.what() << std::endl;
            cfgFile = YAML::Load("{}");
        }

        if(cfgFile.IsNull())
        {
            cfgFile = YAML::Load("[]");
        }

        // 查找任务列表，如存在则使用新指更新，不存在则新增
        // if(cfgFile[nameStr].IsDefined())
        // {
        //     std::cout << "this task is already exist, please reset one!" << std::endl;
        // }

        // 清空原有值
        cfgFile[nameStr] = YAML::Load("[]");
        // 更新新值
        foreach(QString t, topicList)
        {
            cfgFile[nameStr].push_back(t.toStdString());
        }

        // 保存至文件
        std::ofstream fout(mCfgFile.toStdString());
        fout << cfgFile;
    }
}