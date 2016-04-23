#ifndef SCHEMA_H
#define SCHEMA_H

#include <QList>
#include <QMap>

#include "table.h"

class Schema
{
public:
    Schema();

    QList<Table> getTables() const;
    void setTables(const QList<Table> &tables);
    void addTable(Table &table);
    Table* getTable(QString name);

private:
    QMap<QString, Table> mapTables;
};

#endif // SCHEMA_H
