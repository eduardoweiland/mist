#ifndef CREATECONNECTIONDIALOG_H
#define CREATECONNECTIONDIALOG_H

#include "ui_createconnectiondialog.h"

#include "../model/connectionmodel.h"

class CreateConnectionDialog : public QDialog, private Ui::CreateConnectionDialog
{
    Q_OBJECT

public:
    explicit CreateConnectionDialog(ConnectionModel *model, QWidget *parent = 0);

public slots:
    void accept();

private:
    ConnectionModel *model;
};

#endif // CREATECONNECTIONDIALOG_H
