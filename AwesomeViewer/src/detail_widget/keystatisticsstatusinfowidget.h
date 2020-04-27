#ifndef KEYSTATISTICSSTATUSINFOWIDGET_H
#define KEYSTATISTICSSTATUSINFOWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QTableWidget>
#include <QEvent>

#include <QAction>


class KeyStatisticsStatusInfoWidget : public QWidget
{
  Q_OBJECT
public:
  explicit KeyStatisticsStatusInfoWidget(QWidget *parent = nullptr);

private:
  QTableWidget *mTableWidget;

protected:
//  bool eventFilter(QObject *obj, QEvent *event) override;

signals:

public slots:
};

#endif // KEYSTATISTICSSTATUSINFOWIDGET_H
