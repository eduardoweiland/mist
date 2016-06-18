#ifndef MAINWIZARD_H
#define MAINWIZARD_H

#include <QList>

#include "ui_mainwizard.h"

#include "../entity/mistproject.h"
#include "../entity/query.h"

class QKeyEvent;

class MainWizard : public QWizard, private Ui::MainWizard
{
    Q_OBJECT

public:
    explicit MainWizard(QWidget *parent = 0);

    MistProject project;

protected:
    void keyPressEvent(QKeyEvent *e);

private slots:

    //! \brief Shows a dialog containing information about MIST.
    void about(void);
};

#endif // MAINWIZARD_H
