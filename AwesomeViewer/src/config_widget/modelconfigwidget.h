#ifndef MODELCONFIGWIDGET_H
#define MODELCONFIGWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QList>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QCompleter>
#include <QMessageBox>
#include <QInputDialog>

#include <functional>

#include "common_widget/edittabwidget.h"
#include "utilities/rostools.h"

// 每条监测项都是由这个类来显示的
class ModelConfigItem : public QObject
{
    Q_OBJECT
public:
    ModelConfigItem(const QString &name, bool readOnly = false, QWidget *parent = nullptr);
    ~ModelConfigItem();

    static const QStringList itemNameList;
    inline const QList<QWidget*> getItemList() { return mItemList; }

public:

    QLineEdit *mName;
    QComboBox *mTopic;
    QComboBox *mTopicType;
    QLineEdit *mParam;
    QComboBox *mParamType;
    QDoubleSpinBox *mValueMin;
    QDoubleSpinBox *mValueMax;
    QDoubleSpinBox *mHzMin;
    QDoubleSpinBox *mHzMax;
    QWidget *mCfgWidget;

    const QList<QWidget*> mItemList;
private slots:
    void topicChanged(const QString &t);
signals:
    void remove();

};

// 这个类是通用的模块参数监测配置页面
class ModelConfigTable : public QWidget
{
    Q_OBJECT
public:
    explicit ModelConfigTable(QWidget *parent = nullptr, QString modeLabel = "");
    ~ModelConfigTable();
    inline bool isClosable() { return mIsClosable; }
    inline void setClosable(bool closable) { mIsClosable = closable; }

    void addItem(ModelConfigItem *item);
    inline void setLabel(const QString &label){ mModelLabel = label; }
    inline QString getLabel() { return mModelLabel; }

protected:
    QTableWidget *mTableWidget;

private:
    bool mIsClosable;
    QList<ModelConfigItem*> mItemList;

    QString mModelLabel;


public slots:
    void addItem();
    void updateCfg();
    void removeItem(QWidget *item);
};

// 这个类用来管理参数监测模块
class ModelConfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ModelConfigWidget(QWidget *parent = nullptr);
    ~ModelConfigWidget();

private:
    EditTabWidget *mTableWidget;
    YAML::Node mModelCfgNode;

public slots:
    void addModel();
    void removeModel(int index);
    void renameModel(int index, QString newTabText, QString lastTabText);

signals:

};

#endif // MODELCONFIGWIDGET_H
