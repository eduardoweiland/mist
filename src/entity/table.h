#ifndef TABLE_H
#define TABLE_H

#include <QDebug>
#include <QList>
#include <QString>

#include "foreignkey.h"
#include "tablecolumn.h"

class Table
{
public:
    Table();

    QString getName() const;
    void setName(const QString &value);

    int getRowCount() const;
    void setRowCount(int value);

    QList<TableColumn> getColumns() const;
    void setColumns(const QList<TableColumn> &value);
    void addColumn(const TableColumn &value);
    const TableColumn* getColumn(const QString name) const;

    QStringList getPrimaryKey() const;
    void setPrimaryKey(const QStringList &value);
    void addPrimaryKey(const QString &value);

    QList<ForeignKey> getForeignKeys() const;
    void setForeignKeys(const QList<ForeignKey> &value);
    void addForeignKey(const ForeignKey &value);

private:
    QString name;
    int rowCount;
    QList<TableColumn> columns;
    QStringList primaryKey;
    QList<ForeignKey> foreignKeys;
};

QDebug operator<<(QDebug debug, const Table &table);

#endif // TABLE_H
