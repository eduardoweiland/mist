#include <QMessageBox>
#include <QDebug>

#include "mainwindow.h"
#include "aboutdialog.h"
#include "connectionlistwidget.h"
#include "../core/embeddeddatabase.h"
#include "../core/loghandler.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);

//    setCentralWidget(new ConnectionListWidget(this));

    connect(actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(LogHandler::getInstance(), SIGNAL(message(QString)), this, SLOT(logHandler(QString)));
}

MainWindow::~MainWindow()
{
    qInstallMessageHandler(0);
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

void MainWindow::startServer()
{
    EmbeddedDatabase db;
    db.start();
}


void MainWindow::logHandler(const QString &msg)
{
    logView->appendPlainText(msg);
}
