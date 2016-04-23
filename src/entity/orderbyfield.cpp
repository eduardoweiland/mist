#include "orderbyfield.h"

OrderByField::OrderByField()
{

}

QString OrderByField::getTable() const
{
    return table;
}

void OrderByField::setTable(const QString &value)
{
    table = value;
}

QString OrderByField::getField() const
{
    return field;
}

void OrderByField::setField(const QString &value)
{
    field = value;
}

OrderByField::Direction OrderByField::getDir() const
{
    return dir;
}

void OrderByField::setDir(const Direction &value)
{
    dir = value;
}

QDebug operator<<(QDebug debug, const OrderByField &obf)
{
    debug.noquote() << obf.getTable() << '.' << obf.getField();

    return debug;
}
