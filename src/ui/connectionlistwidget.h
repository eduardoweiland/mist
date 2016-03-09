#ifndef CONNECTIONLISTWIDGET_H
#define CONNECTIONLISTWIDGET_H

#include "ui_connectionlistwidget.h"
#include "../model/connectionmodel.h"

class ConnectionListWidget : public QWidget, private Ui::ConnectionListWidget
{
    Q_OBJECT

public:
    explicit ConnectionListWidget(QWidget *parent = 0);

private slots:
    void addConnection();
    void removeConnection();

private:
    ConnectionModel *model;
};

#endif // CONNECTIONLISTWIDGET_H
