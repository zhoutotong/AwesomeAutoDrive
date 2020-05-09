#ifndef STATEWIDGET_H
#define STATEWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QEvent>
#include <QScrollArea>

#include <iostream>

#include "infowidget.h"

class StateWidget : public QWidget
{
  Q_OBJECT
public:
  explicit StateWidget(QWidget *parent = nullptr);

private:

  QVBoxLayout *mLayout;
  QHBoxLayout *mTopLayout;
  QHBoxLayout *mMainLayout;
  QVBoxLayout *mInfoLayout;

  QWidget *mKeyStatisticsInfoWidget;

protected:
  bool eventFilter(QObject *obj, QEvent *event) override;

private:
  void __init();
  void __showAllWidget();
  void __showOneWidget(QWidget *w);
  void __addInfoWidget(QLayout *l, InfoWidget *w);

signals:

public slots:
  void changeStatus();
};

#endif // STATEWIDGET_H
