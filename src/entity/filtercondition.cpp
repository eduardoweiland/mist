#include "filtercondition.h"

FilterCondition::FilterCondition()
{

}

QString FilterCondition::getTable() const
{
    return table;
}

void FilterCondition::setTable(const QString &value)
{
    table = value;
}

QString FilterCondition::getField() const
{
    return field;
}

void FilterCondition::setField(const QString &value)
{
    field = value;
}

FilterCondition::Type FilterCondition::getType() const
{
    return type;
}

void FilterCondition::setType(const Type &value)
{
    type = value;
}
