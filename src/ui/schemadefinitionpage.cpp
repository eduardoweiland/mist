#include <QMessageBox>

#include "schemadefinitionpage.h"
#include "fileopener.h"
#include "mainwizard.h"
#include "../core/schemadefinitionreader.h"

SchemaDefinitionPage::SchemaDefinitionPage(QWidget *parent) :
    QWizardPage(parent)
{
    setupUi(this);
}

bool SchemaDefinitionPage::isComplete() const
{
    return completed;
}

void SchemaDefinitionPage::loadSchemaFile()
{
    MainWizard *mainWizard = static_cast<MainWizard*>(wizard());
    SchemaDefinitionReader reader;
    QFile file;

    editSelectedFileName->setText(QString());

    bool loaded = FileOpener::selectXmlFile(
        this,
        tr("Select schema definition file"),
        tr("MIST Schema Definition File (*.msdf)"),
        &reader,
        &file
    );

    if (loaded) {
        editSelectedFileName->setText(file.fileName());

        QMessageBox::information(
            this,
            tr("File loaded"),
            tr("Successfully loaded %1 tables from definition file").arg(reader.getTables().size())
        );

        mainWizard->project.setTables(reader.getTables());

        tableListWidget->setTables(reader.getTables());
        completed = true;
        emit(completeChanged());
    }
}
