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

ModelConfigTable::ModelConfigTable(QWidget *parent) : QWidget(parent)
  , mTableWidget(new QTableWidget(this))
  , mIsClosable(true)
{
    mTableWidget->setColumnCount(ModelConfigItem::itemNameList.size());
    mTableWidget->setHorizontalHeaderLabels(ModelConfigItem::itemNameList);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(mTableWidget);

    QPushButton *addBtn = new QPushButton("添加");
    layout->addWidget(addBtn, Qt::AlignLeft);
    connect(addBtn, SIGNAL(clicked()), this, SLOT(addItem()));
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

    // 初始化车辆管理，这个页面生命周期与主程序相同，管理要显示的状态信息
    InfoModelConfigTable &infoTable = InfoModelConfigTable::getInstance();
    infoTable.setClosable(false);// 不允许关闭
    mTableWidget->addTab(&infoTable, "车辆信息设置");
    connect(mTableWidget, &EditTabWidget::tabAdded, this, &ModelConfigWidget::addModel);
    connect(mTableWidget, &EditTabWidget::tabCloseRequested, this, &ModelConfigWidget::removeModel);
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
    ModelConfigTable *item = new ModelConfigTable(this);
    mTableWidget->addTab(item, "new model");
    mTableWidget->setCurrentIndex(mTableWidget->indexOf(item));
}

void ModelConfigWidget::removeModel(int index)
{
    if(!static_cast<ModelConfigTable*>(mTableWidget->widget(index))->isClosable()) return;
    mTableWidget->removeTab(index);
}
