#ifndef SCHEMACREATOR_H
#define SCHEMACREATOR_H

#include <QList>

#include "../entity/table.h"

class SchemaCreator
{
public:
    SchemaCreator();

    QString getCreateTable(const Table *table);

protected:
    QString getColumnsDefinition(const Table *table);
    QString getColumnType(const TableColumn *column);
    QString getPrimaryKeyDefinition(const Table *table);
    QString getForeignKeysDefinition(const Table *table);
};

#endif // SCHEMACREATOR_H
