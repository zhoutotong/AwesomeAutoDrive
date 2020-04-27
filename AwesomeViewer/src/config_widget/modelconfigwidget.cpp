#include "modelconfigwidget.h"
#include "common_widget/edittabwidget.h"
#include <QDebug>


const QStringList ModelConfigItem::itemNameList = {"名称", "话题", "类型", "参数", "参数类型", "参数最小值", "参数最大值", "频率最小值", "频率最大值", "选项"};

ModelConfigItem::ModelConfigItem(const QString &name, bool readOnly,
QWidget *parent) : QObject(parent)
  , mName(new QLineEdit(name))
  , mTopic(new QComboBox())
  , mTopicType(new QComboBox())
  , mParam(new QLineEdit())
  , mParamType(new QComboBox())
  , mValueMin(new QDoubleSpinBox())
  , mValueMax(new QDoubleSpinBox())
  , mHzMin(new QDoubleSpinBox())
  , mHzMax(new QDoubleSpinBox())
  , mCfgWidget(new QWidget())
  , mItemList({mName, mTopic, mTopicType, mParam, mParamType, mValueMin, mValueMax, mHzMin, mHzMax, mCfgWidget})
{
    const QStringList paramTypes = {"Int", "Float32", "Float64"};
    mParamType->addItems(paramTypes);

    // 初始化话题选择控件
    mTopic->setEditable(true);
    mTopicType->setEditable(true);
    QStringList topicList;
    std::map<std::string, std::string> ts = utilities::RosTools::getTopicList();
    QStringList strings;
    for(auto itor = ts.begin(); itor != ts.end(); itor++)
    {
        mTopic->addItem(QString::fromStdString(itor->first));
        mTopicType->addItem(QString::fromStdString(itor->second));
        strings.append(QString::fromStdString(itor->first));
    }
    connect(mTopic, &QComboBox::currentTextChanged, this, &ModelConfigItem::topicChanged);
    // 设置自动补全
    QCompleter *completer = new QCompleter(strings, this);
    completer->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
    mTopic->setCompleter(completer);

    // 初始化选项控件
    QHBoxLayout *cfgLayout = new QHBoxLayout(mCfgWidget);
    cfgLayout->setMargin(0);
    QPushButton *removeBtn = new QPushButton("删除", mCfgWidget);
    removeBtn->setEnabled(!readOnly);
    cfgLayout->addWidget(removeBtn);
    connect(removeBtn, &QPushButton::clicked, this, &ModelConfigItem::remove);

    // 控件是否可编辑
    if(readOnly)
    {
        mName->setEnabled(!readOnly);
        mName->setStyleSheet("background:white; color:black");
    }
}

ModelConfigItem::~ModelConfigItem()
{

}

void ModelConfigItem::topicChanged(const QString &t)
{
    std::map<std::string, std::string> ts = utilities::RosTools::getTopicList();
    
    auto itor = ts.find(t.toStdString());
    if(itor != ts.end())
    {
        mTopicType->setCurrentText(QString::fromStdString(itor->second));
    }
}

ModelConfigTable::ModelConfigTable(QWidget *parent, QString modeLabel) : QWidget(parent)
  , mTableWidget(new QTableWidget(this))
  , mIsClosable(true)
  , mModelLabel(modeLabel)
{
    mTableWidget->setColumnCount(ModelConfigItem::itemNameList.size());
    mTableWidget->setHorizontalHeaderLabels(ModelConfigItem::itemNameList);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(mTableWidget);

    QHBoxLayout *ctlLayout = new QHBoxLayout();
    ctlLayout->setAlignment(Qt::AlignLeft);
    layout->addLayout(ctlLayout, Qt::AlignLeft);
    QPushButton *addBtn = new QPushButton("添加");
    addBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ctlLayout->addWidget(addBtn, Qt::AlignLeft);
    connect(addBtn, SIGNAL(clicked()), this, SLOT(addItem()));
    QPushButton *updateBtn = new QPushButton("更新");
    updateBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ctlLayout->addWidget(updateBtn, Qt::AlignLeft);
    connect(updateBtn, &QPushButton::clicked, this, &ModelConfigTable::updateCfg);

    // 从配置文件中读入item
    QString cfgFile = QString::fromStdString(utilities::CfgFileHelper::getModelCfgDir() + 
                    mModelLabel.toStdString() + ".yaml");
    YAML::Node n;
    std::cout << "read cfg file:" << cfgFile.toStdString() << std::endl;
    // 如果配置文件不存在就新建一个空的出来
    if(!utilities::CfgFileHelper::checkFileExist(cfgFile.toStdString()))
    {
        n = YAML::Load("{}");
        utilities::CfgFileHelper::writeYAML2File(n, cfgFile.toStdString());
    }
    else
    {
        n = YAML::LoadFile(cfgFile.toStdString());
    }
    std::cout << "yaml file: " << n << std::endl;
    // 遍历配置文件中的元素，创建item
    for(YAML::Node::iterator top = n.begin(); top != n.end(); top++)
    {
        std::string topic = top->first.as<std::string>();
        std::string topicType = top->second["type"].as<std::string>();
        std::string hzMin = top->second["hz_min"].as<std::string>();
        std::string hzMax = top->second["hz_max"].as<std::string>();

        for(auto para = top->second["params"].begin(); para != top->second["params"].end(); para++)
        {
            std::string param = para->first.as<std::string>();
            std::string name = para->second["name"].as<std::string>();
            std::string paramType = para->second["type"].as<std::string>();
            std::string paramValMin = para->second["min"].as<std::string>();
            std::string paramValMax = para->second["max"].as<std::string>();

            ModelConfigItem *item = new ModelConfigItem(QString::fromStdString(name), false, this);

            item->mTopic->setEditText(QString::fromStdString(topic));
            item->mTopicType->setEditText(QString::fromStdString(topicType));
            item->mParam->setText(QString::fromStdString(param));
            item->mParamType->setEditText(QString::fromStdString(paramType));
            item->mValueMin->setValue(QString::fromStdString(paramValMin).toDouble());
            item->mValueMax->setValue(QString::fromStdString(paramValMax).toDouble());
            item->mHzMin->setValue(QString::fromStdString(hzMin).toDouble());
            item->mHzMax->setValue(QString::fromStdString(hzMax).toDouble());
            addItem(item);
        }


    }

}

ModelConfigTable::~ModelConfigTable()
{
    // 释放 item 列表中的全部资源
    foreach(auto itor, mItemList)
    {
        delete itor;
    }
}

void ModelConfigTable::addItem(ModelConfigItem *item)
{
    int currentCnt = mTableWidget->rowCount();
    mTableWidget->setRowCount(currentCnt + 1);
    // int i = 0;
    // for(auto itor = item->getItemList().begin(); itor != item->getItemList().end(); itor++)
    for(int i = 0; i < item->getItemList().size(); i++)
    {
        mTableWidget->setCellWidget(currentCnt, i, item->getItemList().at(i));
    }
    connect(item, &ModelConfigItem::remove, std::bind(&ModelConfigTable::removeItem, this, 
        item->getItemList().at(0)));

    // 添加到列表进行维护
    mItemList.append(item);
}

void ModelConfigTable::updateCfg()
{
    if(mModelLabel.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "模块名称不能为空！");
    }
    YAML::Node root = YAML::Load("{}");
    foreach(auto itor, mItemList)
    {
        std::string topic = itor->mTopic->currentText().toStdString();
        std::string name = itor->mName->text().toStdString();
        std::string topicType = itor->mTopicType->currentText().toStdString();
        std::string param = itor->mParam->text().toStdString();
        std::string paramType = itor->mParamType->currentText().toStdString();
        std::string paramValMin = itor->mValueMin->text().toStdString();
        std::string paramValMax = itor->mValueMax->text().toStdString();
        std::string hzMin = itor->mHzMin->text().toStdString();
        std::string hzMax = itor->mHzMax->text().toStdString();

        root[topic]["type"] = topicType;
        root[topic]["hz_min"] = hzMin;
        root[topic]["hz_max"] = hzMax;

        root[topic]["params"][param]["name"] = name;
        root[topic]["params"][param]["type"] = paramType;
        root[topic]["params"][param]["min"] = paramValMin;
        root[topic]["params"][param]["max"] = paramValMax;
    }

    std::cout << root << std::endl;
    std::string cfgDir = utilities::CfgFileHelper::getModelCfgDir();
    utilities::CfgFileHelper::checkAndCreateFile(cfgDir);
    utilities::CfgFileHelper::writeYAML2File(root, 
            cfgDir + mModelLabel.toStdString() + ".yaml");

}

void ModelConfigTable::removeItem(QWidget *item)
{
    // 查找要删除的item
    int cnt = mTableWidget->rowCount();
    int ind = -1;
    for(int i = 0; i < cnt; i++)
    {
        if(mTableWidget->cellWidget(i, 0) == item)
        {
            ind = i;
            break;
        }
    }

    // 如果找到了就删除，否则不处理
    if(ind != -1)
    {
        // 首先释放控件资源，然后移除表格中的位置
        for(int m = 0; m < ModelConfigItem::itemNameList.size(); m++)
        {
            delete mTableWidget->cellWidget(ind, m);
        }
        mTableWidget->removeRow(ind);

        // 释放item对象资源，并从item列表中移除
        delete mItemList.at(ind);
        mItemList.removeAt(ind);
    }
}

void ModelConfigTable::addItem()
{
    addItem(new ModelConfigItem("new item", false, this));
}

InfoModelConfigTable::InfoModelConfigTable(QWidget *parent) : ModelConfigTable(parent)
{
    addItem(new ModelConfigItem("车速", true, this));
    addItem(new ModelConfigItem("方向盘", true, this));
}

ModelConfigWidget::ModelConfigWidget(QWidget *parent) : QWidget(parent)
  , mTableWidget(new EditTabWidget(this))
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(mTableWidget);

    mTableWidget->setMovable(true);
    mTableWidget->setTabsClosable(true);
    connect(mTableWidget, &EditTabWidget::tabAdded, this, &ModelConfigWidget::addModel);
    connect(mTableWidget, &EditTabWidget::tabCloseRequested, this, &ModelConfigWidget::removeModel);
    connect(mTableWidget, &EditTabWidget::tabTextChanged, this, &ModelConfigWidget::renameModel);

    // 初始化车辆管理，这个页面生命周期与主程序相同，管理要显示的状态信息，不通过配置文件管理
    InfoModelConfigTable &infoTable = InfoModelConfigTable::getInstance();
    infoTable.setClosable(false);// 不允许关闭
    infoTable.setLabel("truck_info");
    mTableWidget->addTab(&infoTable, "车辆信息设置");

    // 查找模块管理配置文件是否存在，不存在就新建
    QString cfgFile = QString::fromStdString(utilities::CfgFileHelper::getModelCfgFile());
    if(!utilities::CfgFileHelper::checkFileExist(cfgFile.toStdString()))
    {
        YAML::Node n = YAML::Load("{}");
        std::ofstream fout(cfgFile.toStdString());
        fout << n;
    }

    // 文件存在的情况，使用配置文件来初始化界面
    YAML::Node n = YAML::LoadFile(cfgFile.toStdString());
    if(!n.IsMap())
    {
        // 如果配置文件损坏则清空重建
        QMessageBox::critical(this, "Error", "配置文件错误，清空重建！");
        YAML::Node n = YAML::Load("{}");
        std::stringstream ss;
        ss << n;
        FILE *fd = fopen(cfgFile.toStdString().c_str(), "w");
        fwrite(ss.str().c_str(), 1, ss.str().size(), fd);
        fclose(fd);
        n = YAML::LoadFile(cfgFile.toStdString());
    }

    // 创建模块
    for(auto itor = n.begin(); itor != n.end(); itor++)
    {
        if(itor->first.as<std::string>() == "truck_info") continue;
        ModelConfigTable *item = new ModelConfigTable(this, QString::fromStdString(itor->first.as<std::string>()));
        mTableWidget->addTab(item, QString::fromStdString(itor->second.as<std::string>()));
    }

    mModelCfgNode = YAML::LoadFile(cfgFile.toStdString());
    mModelCfgNode["truck_info"] = "车辆信息设置";

}

ModelConfigWidget::~ModelConfigWidget()
{
    if(mTableWidget)
    {
        InfoModelConfigTable &infoTable = InfoModelConfigTable::getInstance();
        mTableWidget->removeTab(mTableWidget->indexOf(&infoTable));
        infoTable.setParent(nullptr);// infotable 为全局对象，此处不应该受tabwidget管理，否则将会出现内存问题
    }
}

void ModelConfigWidget::addModel()
{
    
    QInputDialog *inputDialog = new QInputDialog(this);
    inputDialog->setInputMode(QInputDialog::TextInput);
    QString modelName = "";
    // 输入 model 名称，并检查其合法性
    while(true)
    {
        inputDialog->setWindowTitle("输入模块名称");
        inputDialog->setLabelText("模块名称:");
        if(inputDialog->exec() != QInputDialog::Accepted)
        {
            inputDialog->setParent(nullptr);
            delete inputDialog;
            inputDialog = nullptr;
            return;
        }

        modelName = inputDialog->textValue();
        if(modelName.isEmpty())// 不能为空
        {
            QMessageBox::warning(this, "Warning", "模块名称不能为空!");
        }
        else
        {
            break;
        }
        
    }

    // 获取模块标签，并检查其合法性
    QString labelName = "";
    while(true)
    {
        inputDialog->setWindowTitle("输入模块标签");
        inputDialog->setLabelText("模块标签:");
        QRegExp regx("[a-zA-Z0-9_]+$");
        inputDialog->setTextValue("");
        // inputDialog->set
        if(inputDialog->exec() != QInputDialog::Accepted)
        {
            inputDialog->setParent(nullptr);
            delete inputDialog;
            inputDialog = nullptr;
            return;
        }

        labelName = inputDialog->textValue();
        // 检查是否含有中文
        if(!regx.exactMatch(labelName))
        {
            // 检查不通过则返回重新填写
            QMessageBox::warning(this, "Warning", "标签只能使用：英文字符、下划线、数字，请重新输入!");
            inputDialog->setTextValue("");
            continue;
        }
        // 检查是否已存在，存在则提示
        if(mModelCfgNode[labelName.toStdString()].IsDefined())
        {
            QMessageBox::warning(this, "Warning", "标签名称已存在，请重新输入!");
            continue;
        }
        break;
    }

    ModelConfigTable *item = new ModelConfigTable(this);
    item->setLabel(labelName);
    mTableWidget->addTab(item, modelName);
    mTableWidget->setCurrentIndex(mTableWidget->indexOf(item));

    // 写入配置文件
    mModelCfgNode[labelName.toStdString()] = modelName.toStdString();
    std::stringstream ss;
    ss << mModelCfgNode;
    QString cfgFile = QString::fromStdString(utilities::CfgFileHelper::getModelCfgFile());
    FILE *fd = fopen(cfgFile.toStdString().c_str(), "w");
    fwrite(ss.str().c_str(), 1, ss.str().size(), fd);
    fclose(fd);

    inputDialog->setParent(nullptr);
    delete inputDialog;
    inputDialog = nullptr;
    return;

}

void ModelConfigWidget::removeModel(int index)
{
    if(!static_cast<ModelConfigTable*>(mTableWidget->widget(index))->isClosable()) return;

    int res = QMessageBox::warning(this, "Warning", "删除后将无法恢复，删除？", QMessageBox::Yes, QMessageBox::No);

    if(res == QMessageBox::Yes)
    {
        ModelConfigTable *table = static_cast<ModelConfigTable*>(mTableWidget->widget(index));
        // 从配置文件中移除
        mModelCfgNode.remove(table->getLabel().toStdString());
        std::stringstream ss;
        ss << mModelCfgNode;
        QString cfgFile = QString::fromStdString(utilities::CfgFileHelper::getModelCfgFile());
        FILE *fd = fopen(cfgFile.toStdString().c_str(), "w");
        fwrite(ss.str().c_str(), 1, ss.str().size(), fd);
        fclose(fd);

        // 删除对应的配置文件
        std::string nodeCfg = utilities::CfgFileHelper::getModelCfgDir() + table->getLabel().toStdString() + ".yaml";
        remove(nodeCfg.c_str());

        // 释放资源，并从界面中移除
        delete table;
        mTableWidget->removeTab(index);

    }
}

void ModelConfigWidget::renameModel(int index, QString newTabText, QString lastTabText)
{
    ModelConfigTable *table = static_cast<ModelConfigTable*>(mTableWidget->widget(index));
    qDebug() << index;
    mModelCfgNode[table->getLabel().toStdString()] = newTabText.toStdString();
    std::stringstream ss;
    ss << mModelCfgNode;
    QString cfgFile = QString::fromStdString(utilities::CfgFileHelper::getModelCfgFile());
    FILE *fd = fopen(cfgFile.toStdString().c_str(), "w");
    fwrite(ss.str().c_str(), 1, ss.str().size(), fd);
    fclose(fd);
}
