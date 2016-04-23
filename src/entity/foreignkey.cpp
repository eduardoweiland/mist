#include "foreignkey.h"

ForeignKey::ForeignKey()
{

}

QString ForeignKey::getTable() const
{
    return table;
}

void ForeignKey::setTable(const QString &value)
{
    table = value;
}

QList<ForeignKeyColumn> ForeignKey::getColumns() const
{
    return columns;
}

void ForeignKey::setColumns(const QList<ForeignKeyColumn> &value)
{
    columns = value;
}

void ForeignKey::addColumn(const ForeignKeyColumn &value)
{
    columns.append(value);
}

QDebug operator<<(QDebug debug, const ForeignKey &fk)
{
    debug << fk.getTable() << fk.getColumns();

    return debug;
}
