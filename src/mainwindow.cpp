#include <QMessageBox>

#include "mainwindow.h"
#include "aboutdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);
}

void MainWindow::about()
{
    AboutDialog *about = new AboutDialog(this);
    about->setAttribute(Qt::WA_DeleteOnClose);
    about->exec();
}

void MainWindow::aboutQt()
{
    QMessageBox::aboutQt(this, tr("About Qt"));
}
