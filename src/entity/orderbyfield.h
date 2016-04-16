#ifndef ORDERBYFIELD_H
#define ORDERBYFIELD_H

#include <QString>

class OrderByField
{
public:
    OrderByField();

    enum Direction {
        ASC,
        DESC
    };

    QString getTable() const;
    void setTable(const QString &value);

    QString getField() const;
    void setField(const QString &value);

    Direction getDir() const;
    void setDir(const Direction &value);

private:
    QString table;
    QString field;
    Direction dir;
};

#endif // ORDERBYFIELD_H
