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

QStringList JoinTable::getConditionFields() const
{
    QStringList list;
    foreach (FilterCondition condition, conditions) {
        list << condition.getField();
    }
    return list;
}

void JoinTable::setConditions(const QList<FilterCondition> &value)
{
    conditions = value;
}

void JoinTable::addCondition(const FilterCondition &value)
{
    conditions.append(value);
}

QDebug operator<<(QDebug debug, const JoinTable &jt)
{
    switch (jt.getType()) {
        case JoinTable::INNER:
            debug << "INNER JOIN";
            break;
        case JoinTable::LEFT:
            debug << "LEFT JOIN";
            break;
        case JoinTable::RIGHT:
            debug << "RIGHT JOIN";
            break;
        default:
            debug << jt.getType();
            break;
    }

    debug << jt.getTable() << jt.getConditions();

    return debug;
}
