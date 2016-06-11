#ifndef MAINWIZARD_H
#define MAINWIZARD_H

#include "ui_mainwizard.h"

class QKeyEvent;

class MainWizard : public QWizard, private Ui::MainWizard
{
    Q_OBJECT

public:
    explicit MainWizard(QWidget *parent = 0);

protected:
    void keyPressEvent(QKeyEvent *e);

private slots:

    //! \brief Shows a dialog containing information about MIST.
    void about(void);
};

#endif // MAINWIZARD_H
