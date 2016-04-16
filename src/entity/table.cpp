#include "table.h"

Table::Table()
{

}

QString Table::getName() const
{
    return name;
}

void Table::setName(const QString &value)
{
    name = value;
}

int Table::getRowCount() const
{
    return rowCount;
}

void Table::setRowCount(int value)
{
    rowCount = value;
}

QList<TableColumn> Table::getColumns() const
{
    return columns;
}

void Table::setColumns(const QList<TableColumn> &value)
{
    columns = value;
}

void Table::addColumn(const TableColumn &value)
{
    columns.append(value);
}

QStringList Table::getPrimaryKey() const
{
    return primaryKey;
}

void Table::setPrimaryKey(const QStringList &value)
{
    primaryKey = value;
}

void Table::addPrimaryKey(const QString &value)
{
    primaryKey.append(value);
}

QList<ForeignKey> Table::getForeignKeys() const
{
    return foreignKeys;
}

void Table::setForeignKeys(const QList<ForeignKey> &value)
{
    foreignKeys = value;
}

void Table::addForeignKey(const ForeignKey &value)
{
    foreignKeys.append(value);
}
