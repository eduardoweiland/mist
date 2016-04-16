#ifndef FOREIGNKEY_H
#define FOREIGNKEY_H

#include <QList>
#include <QString>

#include "foreignkeycolumn.h"

class ForeignKey
{
public:
    ForeignKey();

    QString getTable() const;
    void setTable(const QString &value);

    QList<ForeignKeyColumn> getColumns() const;
    void setColumns(const QList<ForeignKeyColumn> &value);
    void addColumn(const ForeignKeyColumn &value);

private:
    QString table;
    QList<ForeignKeyColumn> columns;
};

#endif // FOREIGNKEY_H
