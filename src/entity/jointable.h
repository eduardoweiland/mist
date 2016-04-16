#ifndef JOINTABLE_H
#define JOINTABLE_H

#include <QList>

#include "filtercondition.h"

class QString;

class JoinTable
{
public:
    JoinTable();

    enum Type {
        INNER,
        LEFT,
        RIGHT
    };

    Type getType() const;
    void setType(const Type &value);

    QString getTable() const;
    void setTable(const QString &value);

    QList<FilterCondition> getConditions() const;
    void setConditions(const QList<FilterCondition> &value);
    void addCondition(const FilterCondition &value);

private:
    Type type;
    QString table;
    QList<FilterCondition> conditions;
};

#endif // JOINTABLE_H
