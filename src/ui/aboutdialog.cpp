#include "aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);

    version->setText(tr("Version %1").arg(qApp->applicationVersion()));
}
