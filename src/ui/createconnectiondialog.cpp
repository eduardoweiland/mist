#include <iostream>

#include "createconnectiondialog.h"


CreateConnectionDialog::CreateConnectionDialog(ConnectionModel *model, QWidget *parent) :
    QDialog(parent), model(model)
{
    setupUi(this);
}

void CreateConnectionDialog::accept()
{
    Connection *conn = new Connection();
    conn->setDisplayName(inputDisplayName->text());
    conn->setHostName(inputHostName->text());
    conn->setPortNumber(inputPortNumber->value());
    conn->setUserName(inputUserName->text());
    conn->setPassword(inputPassword->text());
    conn->setDatabase(inputDatabase->text());

    model->create(conn);

    QDialog::accept();
}
