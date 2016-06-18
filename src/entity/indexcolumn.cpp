#include "indexcolumn.h"

IndexColumn::IndexColumn()
    : length(0)
{
}

const QString IndexColumn::getColumn() const
{
    return column;
}

void IndexColumn::setColumn(const QString value)
{
    column = value;
}

int IndexColumn::getLength() const
{
    return length;
}

void IndexColumn::setLength(int value)
{
    length = value;
}

bool IndexColumn::operator==(IndexColumn &other) const
{
    return (column == other.column && length == other.length);
}

bool IndexColumn::operator==(const IndexColumn &other) const
{
    return (column == other.column && length == other.length);
}

QDebug operator<<(QDebug debug, const IndexColumn &ic)
{
    debug << ic.getColumn();

    return debug;
}
