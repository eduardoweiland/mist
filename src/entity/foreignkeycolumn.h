#ifndef FOREIGNKEYCOLUMN_H
#define FOREIGNKEYCOLUMN_H

#include <QDebug>
#include <QString>

class ForeignKeyColumn
{
public:
    ForeignKeyColumn();

    QString getName() const;
    void setName(const QString &value);

    QString getReferenced() const;
    void setReferenced(const QString &value);

private:
    QString name;
    QString referenced;
};

QDebug operator<<(QDebug debug, const ForeignKeyColumn &fkc);

#endif // FOREIGNKEYCOLUMN_H
