#ifndef EDITTABWIDGET_H
#define EDITTABWIDGET_H

#include <QWidget>
#include <QTabWidget>
#include <QTabBar>
#include <QEvent>
#include <QLineEdit>
#include <QKeyEvent>

#include <QPushButton>

class EditTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    EditTabWidget(QWidget *parent = nullptr);

private:
    QTabBar *mBar;
    int mCurrentSelectTabIndex;
    QLineEdit *mTabEditLine;
    QPushButton *mAddBtn;
protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

public slots:
    void cancelLineEdit();
    void confirmLineEdit();

signals:
    void tabTextChanged(int index, QString tabText);
    void tabAdded();
};

#endif // EDITTABWIDGET_H
