#include "indexcolumn.h"

IndexColumn::IndexColumn()
{

}

const TableColumn *IndexColumn::getColumn() const
{
    return column;
}

void IndexColumn::setColumn(const TableColumn *value)
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

QDebug operator<<(QDebug debug, const IndexColumn &ic)
{
    debug << ic.getColumn()->getName();

    return debug;
}
