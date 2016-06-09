#ifndef MAINWIZARD_H
#define MAINWIZARD_H

#include "ui_mainwizard.h"

class MainWizard : public QWizard, private Ui::MainWizard
{
    Q_OBJECT

public:
    explicit MainWizard(QWidget *parent = 0);
};

#endif // MAINWIZARD_H
