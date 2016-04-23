#include "foreignkeycolumn.h"

ForeignKeyColumn::ForeignKeyColumn()
{

}

QString ForeignKeyColumn::getName() const
{
    return name;
}

void ForeignKeyColumn::setName(const QString &value)
{
    name = value;
}

QString ForeignKeyColumn::getReferenced() const
{
    return referenced;
}

void ForeignKeyColumn::setReferenced(const QString &value)
{
    referenced = value;
}

QDebug operator<<(QDebug debug, const ForeignKeyColumn &fkc)
{
    debug << fkc.getName() << '=' << fkc.getReferenced();

    return debug;
}
