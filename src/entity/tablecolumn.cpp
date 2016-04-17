#include "tablecolumn.h"

TableColumn::TableColumn()
{

}

QString TableColumn::getName() const
{
    return name;
}

void TableColumn::setName(const QString &value)
{
    name = value;
}

TableColumn::Type TableColumn::getType() const
{
    return type;
}

void TableColumn::setType(const Type &value)
{
    type = value;
}

bool TableColumn::getNullable() const
{
    return nullable;
}

void TableColumn::setNullable(bool value)
{
    nullable = value;
}

int TableColumn::getLength() const
{
    return length;
}

void TableColumn::setLength(int value)
{
    length = value;
}

int TableColumn::getPrecision() const
{
    return precision;
}

void TableColumn::setPrecision(int value)
{
    precision = value;
}

int TableColumn::getDistinctValues() const
{
    return distinctValues;
}

void TableColumn::setDistinctValues(int value)
{
    distinctValues = value;
}
