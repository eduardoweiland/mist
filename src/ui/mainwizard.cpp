#include <QKeyEvent>

#include "mainwizard.h"
#include "aboutdialog.h"

MainWizard::MainWizard(QWidget *parent) :
    QWizard(parent)
{
    setupUi(this);

    connect(this, SIGNAL(helpRequested()), this, SLOT(about()));

    setButtonText(HelpButton, tr("&About"));
    setButtonText(BackButton, tr("< &Back"));
    setButtonText(NextButton, tr("&Next >"));
}

void MainWizard::keyPressEvent(QKeyEvent *e)
{
    if (e->key() != Qt::Key_Escape) {
        QWizard::keyPressEvent(e);
    }
}

void MainWizard::about()
{
    AboutDialog *about = new AboutDialog(this);
    about->setAttribute(Qt::WA_DeleteOnClose);
    about->exec();
}
