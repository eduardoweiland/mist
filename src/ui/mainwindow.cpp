#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QDir>
#include <QDebug>

#include "mainwindow.h"
#include "aboutdialog.h"
#include "../core/embeddeddatabase.h"
#include "../core/querylogreader.h"
#include "../core/schemadefinitionreader.h"
#include "../core/loghandler.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);

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

void MainWindow::loadSchemaFile()
{
    SchemaDefinitionReader reader;

    bool loaded = selectAndParseFile(
        tr("Select schema definition file"),
        tr("MIST Schema Definition File (*.msdf)"),
        &reader
    );

    if (loaded) {
        QMessageBox::information(
            this,
            tr("File loaded"),
            tr("Successfully loaded %1 tables from definition file").arg(reader.getTables().size())
        );
    }
}

void MainWindow::loadLogFile()
{
    QueryLogReader reader;

    bool loaded = selectAndParseFile(
        tr("Select query log file"),
        tr("MIST Query Log File (*.mqlf)"),
        &reader
    );

    if (loaded) {
        QMessageBox::information(
            this,
            tr("File loaded"),
            tr("Successfully loaded %1 queries from log file").arg(reader.getQueries().size())
        );
    }
}

bool MainWindow::selectAndParseFile(const QString &title, const QString &filter, AbstractXmlReader *parser)
{
    QString filename = QFileDialog::getOpenFileName(this, title, QDir::homePath(), filter);

    if (filename.isNull()) {
        // No file selected
        return false;
    }

    qInfo() << tr("Selected file: %1").arg(filename);

    QFile logFile(filename);
    if (!logFile.open(QFile::ReadOnly | QFile::Text)) {
        qCritical() << tr("Error opening selected file %1").arg(filename);

        QMessageBox::critical(
            this,
            tr("Error opening file"),
            tr("There was an error opening the selected schema definition file. "
               "Check if you have permissions to read it.")
        );

        return false;
    }

    if (!parser->parse(&logFile)) {
        qCritical() << tr("Error parsing selected file %1: %2")
                       .arg(filename)
                       .arg(parser->getError());

        QMessageBox::critical(
            this,
            tr("Error opening file"),
            tr("There was an error parsing the selected file:\n%1").arg(parser->getError())
        );

        return false;
    }

    return true;
}

void MainWindow::startServer()
{
    EmbeddedDatabase db;
    db.start();
}

void MainWindow::stopServer()
{
    EmbeddedDatabase db;
    db.stop();
}

void MainWindow::logHandler(const QString &msg)
{
    logView->appendPlainText(msg);
}
