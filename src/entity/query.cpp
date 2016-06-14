#include <QList>

#include "query.h"

Query::Query()
{

}

int Query::getId() const
{
    return id;
}

void Query::setId(int value)
{
    id = value;
}

int Query::getCount() const
{
    return count;
}

void Query::setCount(int value)
{
    count = value;
}

QString Query::getSql() const
{
    return sql;
}

void Query::setSql(const QString &value)
{
    sql = value;
}

QStringList Query::getFrom() const
{
    return from;
}

void Query::setFrom(const QStringList &value)
{
    from = value;
}

void Query::addFrom(const QString &value)
{
    from.append(value);
}

QList<JoinTable> Query::getJoins() const
{
    return joins;
}

void Query::setJoins(const QList<JoinTable> &value)
{
    joins = value;
}

void Query::addJoin(const JoinTable &value)
{
    joins.append(value);
}

QList<FilterCondition> Query::getWhere() const
{
    return where;
}

void Query::setWhere(const QList<FilterCondition> &value)
{
    where = value;
}

void Query::addWhere(const FilterCondition &value)
{
    where.append(value);
}

QList<OrderByField> Query::getOrderBy() const
{
    return orderBy;
}

void Query::setOrderBy(const QList<OrderByField> &value)
{
    orderBy = value;
}

void Query::addOrderBy(const OrderByField &value)
{
    orderBy.append(value);
}

QList<GroupByField> Query::getGroupBy() const
{
    return groupBy;
}

void Query::setGroupBy(const QList<GroupByField> &value)
{
    groupBy = value;
}

void Query::addGroupBy(const GroupByField &value)
{
    groupBy.append(value);
}

QStringList Query::getUsedTables() const
{
    QStringList tables = from;

    foreach (JoinTable join, joins) {
        tables.append(join.getTable());
    }

    return tables;
}

QDebug operator<<(QDebug debug, const Query &query)
{
    debug.nospace() << '#' << query.getId() << ' ' << query.getCount() << 'x';
    debug << "FROM" << query.getFrom()
          << "JOINS" << query.getJoins()
          << "WHERE" << query.getWhere()
          << "GROUP BY" << query.getGroupBy()
          << "ORDER BY" << query.getOrderBy();

    return debug;
}
