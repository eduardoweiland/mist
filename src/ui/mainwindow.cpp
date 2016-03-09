#include <iostream>
#include <QMessageBox>
#include <QDebug>

#include "mainwindow.h"
#include "aboutdialog.h"
#include "connectionlistwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);

    setCentralWidget(new ConnectionListWidget(this));

    connect(actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
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
