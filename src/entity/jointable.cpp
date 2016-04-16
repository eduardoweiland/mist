#include <QList>

#include "jointable.h"

JoinTable::JoinTable()
{

}

JoinTable::Type JoinTable::getType() const
{
    return type;
}

void JoinTable::setType(const Type &value)
{
    type = value;
}

QString JoinTable::getTable() const
{
    return table;
}

void JoinTable::setTable(const QString &value)
{
    table = value;
}

QList<FilterCondition> JoinTable::getConditions() const
{
    return conditions;
}

void JoinTable::setConditions(const QList<FilterCondition> &value)
{
    conditions = value;
}

void JoinTable::addCondition(const FilterCondition &value)
{
    conditions.append(value);
}
