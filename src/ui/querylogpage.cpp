#include <QMessageBox>

#include "querylogpage.h"
#include "fileopener.h"
#include "mainwizard.h"
#include "../core/querylogreader.h"

QueryLogPage::QueryLogPage(QWidget *parent) :
    QWizardPage(parent)
{
    setupUi(this);
}

bool QueryLogPage::isComplete() const
{
    return completed;
}

void QueryLogPage::loadQueriesFile()
{
    MainWizard *mainWizard = static_cast<MainWizard*>(wizard());
    QueryLogReader reader;
    QFile file;

    editSelectedFileName->setText(QString());

    bool loaded = FileOpener::selectXmlFile(
        this,
        tr("Select query log file"),
        tr("MIST Query Log File (*.mqlf)"),
        &reader,
        &file
    );

    if (loaded) {
        editSelectedFileName->setText(file.fileName());

        QMessageBox::information(
            this,
            tr("File loaded"),
            tr("Successfully loaded %1 queries from log file").arg(reader.getQueries().size())
        );

        mainWizard->queries = reader.getQueries();

        queryLogWidget->setQueries(reader.getQueries());
        completed = true;
        emit(completeChanged());
    }
}
