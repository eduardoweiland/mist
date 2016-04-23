#ifndef SCHEMA_H
#define SCHEMA_H

#include <QDebug>
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

QDebug operator<<(QDebug debug, const Schema &schema);

#endif // SCHEMA_H
