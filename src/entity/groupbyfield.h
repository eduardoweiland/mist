#ifndef GROUPBYFIELD_H
#define GROUPBYFIELD_H

#include <QDebug>
#include <QString>

class GroupByField
{
public:
    GroupByField();

    QString getTable() const;
    void setTable(const QString &value);

    QString getField() const;
    void setField(const QString &value);

private:
    QString table;
    QString field;
};

QDebug operator<<(QDebug debug, const GroupByField &gbf);

#endif // GROUPBYFIELD_H
