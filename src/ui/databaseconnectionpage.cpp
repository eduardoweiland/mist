#include <QMessageBox>
#include <QSqlDatabase>

#include "databaseconnectionpage.h"

DatabaseConnectionPage::DatabaseConnectionPage(QWidget *parent) :
    QWizardPage(parent), completed(false)
{
    setupUi(this);
}

bool DatabaseConnectionPage::isComplete() const
{
    return completed;
}

bool DatabaseConnectionPage::testConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(editHostname->text());
    db.setPort(spinPortNumber->value());
    db.setDatabaseName(editDatabaseName->text());
    db.setUserName(editUsername->text());
    db.setPassword(editPassword->text());

    completed = db.open();
    emit(completeChanged());

    return completed;
}

void DatabaseConnectionPage::onTestConnectionButtonClicked()
{
    if (testConnection()) {
        QMessageBox::information(this, tr("Success"), tr("Connection was successfull!"));
    }
    else {
        QMessageBox::critical(this, tr("Error"), tr("Cannot connect to the database with this parameters."));
    }
}
