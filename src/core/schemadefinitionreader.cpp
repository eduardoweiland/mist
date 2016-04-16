#include <QFile>

#include "schemadefinitionreader.h"

SchemaDefinitionReader::SchemaDefinitionReader()
{
}

SchemaDefinitionReader::~SchemaDefinitionReader()
{
}

const QList<Table>& SchemaDefinitionReader::getTables() const
{
    return this->tables;
}

bool SchemaDefinitionReader::parse(QFile *file)
{
    xml.setDevice(file);

    if (xml.readNextStartElement()) {
        if (xml.name() == "schema" && xml.attributes().value("version") == "1.0") {
            readTables();
        }
        else {
            xml.raiseError(QObject::tr("The file is not a valid MIST Schema Definition File."));
        }
    }

    return !xml.error();
}

QString SchemaDefinitionReader::getError() const
{
    return QObject::tr("%1 (line %2, column %3)")
            .arg(xml.errorString())
            .arg(xml.lineNumber())
            .arg(xml.columnNumber());
}

void SchemaDefinitionReader::readTables()
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "schema");

    while (xml.readNextStartElement()) {
        if (xml.name() == "table") {
            readTable();
        }
        else {
            xml.raiseError(QObject::tr("Unknown tag found: %1").arg(xml.name().toString()));
        }
    }
}

void SchemaDefinitionReader::readTable()
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "table");

    Table table;

    table.setName(xml.attributes().value("name").toString());
    table.setRowCount(xml.attributes().value("row-count").toInt());

    while (xml.readNextStartElement()) {
        if (xml.name() == "column") {
            readColumn(&table);
        }
        else if (xml.name() == "primary-key") {
            readPrimaryKey(&table);
        }
        else if (xml.name() == "foreign-key") {
            readForeignKey(&table);
        }
        else {
            xml.raiseError(QObject::tr("Unknown tag found: %1").arg(xml.name().toString()));
        }
    }

    tables.append(table);
}

void SchemaDefinitionReader::readColumn(Table *table)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "column");
    Q_ASSERT(table != nullptr);

    TableColumn column;
    column.setName(xml.attributes().value("name").toString());
    column.setType(xml.attributes().value("type").toString());
    column.setNullable(xml.attributes().value("nullable") == "true");
    column.setLength(xml.attributes().value("length").toInt());
    column.setPrecision(xml.attributes().value("precision").toInt());
    column.setDistinctValues(xml.attributes().value("distinct-values").toInt());

    table->addColumn(column);
    xml.skipCurrentElement();
}

void SchemaDefinitionReader::readPrimaryKey(Table *table)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "primary-key");
    Q_ASSERT(table != nullptr);
    Q_ASSERT(table->getPrimaryKey().isEmpty());

    while (xml.readNextStartElement()) {
        if (xml.name() == "column") {
            table->addPrimaryKey(xml.attributes().value("name").toString());
            xml.skipCurrentElement();
        }
        else {
            xml.raiseError(QObject::tr("Unknown tag found: %1").arg(xml.name().toString()));
        }
    }
}

void SchemaDefinitionReader::readForeignKey(Table *table)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "foreign-key");
    Q_ASSERT(table != nullptr);

    ForeignKey fk;

    while (xml.readNextStartElement()) {
        if (xml.name() == "column") {
            ForeignKeyColumn column;
            column.setName(xml.attributes().value("name").toString());
            column.setReferenced(xml.attributes().value("referenced").toString());

            fk.addColumn(column);
            xml.skipCurrentElement();
        }
        else {
            xml.raiseError(QObject::tr("Unknown tag found: %1").arg(xml.name().toString()));
        }
    }

    table->addForeignKey(fk);
}
