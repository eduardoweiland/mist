#ifndef DATABASECONNECTIONPAGE_H
#define DATABASECONNECTIONPAGE_H

#include "ui_databaseconnectionpage.h"

class DatabaseConnectionPage : public QWizardPage, private Ui::DatabaseConnectionPage
{
    Q_OBJECT

public:
    explicit DatabaseConnectionPage(QWidget *parent = 0);
    bool isComplete() const;

protected:
    bool testConnection();

private slots:
    void onTestConnectionButtonClicked();

private:
    bool completed;
};

#endif // DATABASECONNECTIONPAGE_H
