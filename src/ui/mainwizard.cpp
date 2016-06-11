#include <QKeyEvent>

#include "mainwizard.h"

MainWizard::MainWizard(QWidget *parent) :
    QWizard(parent)
{
    setupUi(this);
}

void MainWizard::keyPressEvent(QKeyEvent *e)
{
    if (e->key() != Qt::Key_Escape) {
        QWizard::keyPressEvent(e);
    }
}
