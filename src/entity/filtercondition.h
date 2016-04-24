#ifndef FILTERCONDITION_H
#define FILTERCONDITION_H

#include <QDebug>
#include <QString>

class FilterCondition
{
public:
    FilterCondition();

    enum Type {
        CONST,
        MATCH,
        RANGE,
        LIST,
        LIKE
    };

    QString getTable() const;
    void setTable(const QString &value);

    QString getField() const;
    void setField(const QString &value);

    Type getType() const;
    void setType(const Type &value);

private:
    QString table;
    QString field;
    Type type;
};

QDebug operator<<(QDebug debug, const FilterCondition &fc);

#endif // FILTERCONDITION_H
