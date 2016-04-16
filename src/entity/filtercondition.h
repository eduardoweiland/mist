#ifndef WHERECONDITION_H
#define WHERECONDITION_H

#include <QString>

class FilterCondition
{
public:
    FilterCondition();

    enum Type {
        EXACTMATCH,
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

#endif // WHERECONDITION_H
