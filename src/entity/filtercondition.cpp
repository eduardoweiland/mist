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

QDebug operator<<(QDebug debug, const FilterCondition &fc)
{
    debug << fc.getTable() << '(' << fc.getField() << '=';

    switch (fc.getType()) {
        case FilterCondition::CONST:
            debug << "CONST";
            break;
        case FilterCondition::MATCH:
            debug << "MATCH";
            break;
        case FilterCondition::RANGE:
            debug << "RANGE";
            break;
        case FilterCondition::LIST:
            debug << "LIST";
            break;
        case FilterCondition::LIKE:
            debug << "LIKE";
            break;
        default:
            debug << fc.getType();
            break;
    }

    return debug;
}
