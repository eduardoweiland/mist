#include "groupbyfield.h"

GroupByField::GroupByField()
{

}

QString GroupByField::getTable() const
{
    return table;
}

void GroupByField::setTable(const QString &value)
{
    table = value;
}

QString GroupByField::getField() const
{
    return field;
}

void GroupByField::setField(const QString &value)
{
    field = value;
}

QDebug operator<<(QDebug debug, const GroupByField &gbf)
{
    debug.noquote() << gbf.getTable() << '.' << gbf.getField();

    return debug;
}
