#include "mistproject.h"

MistProject::MistProject()
{
}

QList<Table> MistProject::getTables() const
{
    return mapTables.values();
}

void MistProject::setTables(const QList<Table> &tables)
{
    foreach (Table table, tables) {
        mapTables[table.getName()] = table;
    }
}

void MistProject::addTable(Table &table)
{
    mapTables[table.getName()] = table;
}

Table* MistProject::getTable(QString name)
{
    return &mapTables[name];
}

QDebug operator<<(QDebug debug, const MistProject &project)
{
    debug << project.getTables();

    return debug;
}
