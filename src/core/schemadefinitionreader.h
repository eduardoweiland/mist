#ifndef SCHEMADEFINITIONREADER_H
#define SCHEMADEFINITIONREADER_H

#include <QList>
#include <QXmlStreamReader>

#include "../entity/table.h"

class SchemaDefinitionReader
{
public:
    SchemaDefinitionReader();
    virtual ~SchemaDefinitionReader();

    bool parse(QFile *file);
    QString getError() const;

    const QList<Table>& getTables() const;

private:
    QList<Table> tables;
    QXmlStreamReader xml;

    void readTables();
    void readTable();
    void readColumn(Table *table);
    void readPrimaryKey(Table *table);
    void readForeignKey(Table *table);
};

#endif // SCHEMADEFINITIONREADER_H
