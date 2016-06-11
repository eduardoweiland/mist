#include <QMessageBox>

#include "schemadefinitionpage.h"
#include "fileopener.h"
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
    SchemaDefinitionReader reader;

    bool loaded = FileOpener::selectXmlFile(
        this,
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

        tableListWidget->setTables(reader.getTables());
        completed = true;
        emit(completeChanged());
    }
}
