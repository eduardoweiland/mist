#include <mysql.h>

#include "aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);

    version->setText(tr("Version %1").arg(qApp->applicationVersion()));
    mysqlVersion->setText(tr("MySQL Server version: %1").arg(MYSQL_SERVER_VERSION));
}
