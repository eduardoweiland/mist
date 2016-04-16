#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QDir>
#include <QDebug>

#include "mainwindow.h"
#include "aboutdialog.h"
#include "connectionlistwidget.h"
#include "../core/embeddeddatabase.h"
#include "../core/querylogreader.h"
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

void MainWindow::loadLogFile()
{
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Select query log file"),
                QDir::homePath(),
                tr("MIST Query Log File (*.mqlf)"));

    if (filename.isNull()) {
        // No file selected
        return;
    }

    qInfo() << tr("Query log file %1 selected").arg(filename);

    QFile logFile(filename);
    if (!logFile.open(QFile::ReadOnly | QFile::Text)) {
        qCritical() << tr("Error opening selected file %1").arg(filename);

        QMessageBox::critical(
                    this,
                    tr("Error opening file"),
                    tr("There was an error opening the selected query log file. "
                       "Check if you have permissions to read it."));
        return;
    }

    QueryLogReader reader;
    if (!reader.parse(&logFile)) {
        qCritical() << tr("Error parsing selected file %1: %2")
                       .arg(filename)
                       .arg(reader.getError());

        QMessageBox::critical(
                    this,
                    tr("Error opening file"),
                    tr("There was an error parsing the selected log file:\n%1").arg(reader.getError()));
        return;
    }

    QMessageBox::information(
                this,
                tr("File loaded"),
                tr("Successfully loaded %1 queries from log file").arg(reader.getQueries().size()));
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
