#ifndef QUERY_H
#define QUERY_H

#include <QDebug>
#include <QString>
#include <QList>

#include "filtercondition.h"
#include "groupbyfield.h"
#include "jointable.h"
#include "orderbyfield.h"

class Query
{
public:
    Query();

    int getId() const;
    void setId(int value);

    int getCount() const;
    void setCount(int value);

    QStringList getFrom() const;
    void setFrom(const QStringList &value);
    void addFrom(const QString &value);

    QList<JoinTable> getJoins() const;
    void setJoins(const QList<JoinTable> &value);
    void addJoin(const JoinTable &value);

    QList<FilterCondition> getWhere() const;
    void setWhere(const QList<FilterCondition> &value);
    void addWhere(const FilterCondition &value);

    QList<OrderByField> getOrderBy() const;
    void setOrderBy(const QList<OrderByField> &value);
    void addOrderBy(const OrderByField &value);

    QList<GroupByField> getGroupBy() const;
    void setGroupBy(const QList<GroupByField> &value);
    void addGroupBy(const GroupByField &value);

private:
    int id;
    int count;
    QStringList from;
    QList<JoinTable> joins;
    QList<FilterCondition> where;
    QList<OrderByField> orderBy;
    QList<GroupByField> groupBy;
};

QDebug operator<<(QDebug debug, const Query &query);

#endif // QUERY_H
