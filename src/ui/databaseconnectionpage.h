#ifndef DATABASECONNECTIONPAGE_H
#define DATABASECONNECTIONPAGE_H

#include "ui_databaseconnectionpage.h"

class DatabaseConnectionPage : public QWizardPage, private Ui::DatabaseConnectionPage
{
    Q_OBJECT

public:
    explicit DatabaseConnectionPage(QWidget *parent = 0);
};

#endif // DATABASECONNECTIONPAGE_H
