#include "schema.h"

Schema::Schema()
{
}

QList<Table> Schema::getTables() const
{
    return mapTables.values();
}

void Schema::setTables(const QList<Table> &tables)
{
    foreach (Table table, tables) {
        mapTables[table.getName()] = table;
    }
}

void Schema::addTable(Table &table)
{
    mapTables[table.getName()] = table;
}

Table* Schema::getTable(QString name)
{
    return &mapTables[name];
}

QDebug operator<<(QDebug debug, const Schema &schema)
{
    debug << schema.getTables();

    return debug;
}
