#include <QFile>

#include "schemadefinitionreader.h"

SchemaDefinitionReader::SchemaDefinitionReader() :
    AbstractXmlReader()
{
}

SchemaDefinitionReader::~SchemaDefinitionReader()
{
}

const QList<Table>& SchemaDefinitionReader::getTables() const
{
    return this->tables;
}

bool SchemaDefinitionReader::parse(QIODevice *file)
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
    column.setNullable(xml.attributes().value("nullable") == "true");
    column.setLength(xml.attributes().value("length").toInt());
    column.setPrecision(xml.attributes().value("precision").toInt());
    column.setDistinctValues(xml.attributes().value("distinct-values").toInt());
    column.setNullValues(xml.attributes().value("null-values").toInt());

    if (xml.attributes().value("type") == "varchar") {
        column.setType(TableColumn::VARCHAR);
    }
    else if (xml.attributes().value("type") == "char") {
        column.setType(TableColumn::CHAR);
    }
    else if (xml.attributes().value("type") == "text") {
        column.setType(TableColumn::TEXT);
    }
    else if (xml.attributes().value("type") == "tinyint") {
        column.setType(TableColumn::TINYINT);
    }
    else if (xml.attributes().value("type") == "smallint") {
        column.setType(TableColumn::SMALLINT);
    }
    else if (xml.attributes().value("type") == "integer") {
        column.setType(TableColumn::INTEGER);
    }
    else if (xml.attributes().value("type") == "mediumint") {
        column.setType(TableColumn::MEDIUMINT);
    }
    else if (xml.attributes().value("type") == "bigint") {
        column.setType(TableColumn::BIGINT);
    }
    else if (xml.attributes().value("type") == "boolean") {
        column.setType(TableColumn::BOOLEAN);
    }
    else if (xml.attributes().value("type") == "decimal") {
        column.setType(TableColumn::DECIMAL);
    }
    else if (xml.attributes().value("type") == "date") {
        column.setType(TableColumn::DATE);
    }
    else if (xml.attributes().value("type") == "time") {
        column.setType(TableColumn::TIME);
    }
    else if (xml.attributes().value("type") == "datetime") {
        column.setType(TableColumn::DATETIME);
    }
    else if (xml.attributes().value("type") == "float") {
        column.setType(TableColumn::FLOAT);
    }
    else if (xml.attributes().value("type") == "double") {
        column.setType(TableColumn::DOUBLE);
    }
    else if (xml.attributes().value("type") == "blob") {
        column.setType(TableColumn::BLOB);
    }
    else {
        xml.raiseError(QObject::tr("Invalid type for column found: %1").arg(xml.attributes().value("type").toString()));
    }


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
    fk.setTable(xml.attributes().value("table").toString());

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
