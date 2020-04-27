#ifndef NETWORKINFOWIDGET_H
#define NETWORKINFOWIDGET_H

#include <QWidget>
#include "infowidget.h"

class NetworkInfoWidget : public InfoWidget
{
  Q_OBJECT
public:
  explicit NetworkInfoWidget(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // NETWORKINFOWIDGET_H
