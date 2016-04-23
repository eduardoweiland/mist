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

/*!
 * \see https://dev.mysql.com/doc/refman/5.7/en/storage-requirements.html
 */
int TableColumn::getSize() const
{
    switch (type) {
        case VARCHAR:
        case CHAR:
            return length;
        case DECIMAL:
            return static_cast<int>(floor(length / 9.0) * 4) + ceil((length % 9) / 2.0);
        case BOOLEAN:
        case TINYINT:
            return 1;
        case SMALLINT:
            return 2;
        case MEDIUMINT:
            return 3;
        case INTEGER:
            return 4;
        case BIGINT:
            return 8;
        case DATE:
            return 3;
        case TIME:
            return 3;
        case DATETIME:
            return 5;
        case FLOAT:
            return 4;
        case DOUBLE:
            return 8;
        case TEXT:
        case BLOB:
            return 65535;
    }

    return 0;
}

QDebug operator<<(QDebug debug, const TableColumn &tc)
{
    debug << tc.getName();

    return debug;
}
