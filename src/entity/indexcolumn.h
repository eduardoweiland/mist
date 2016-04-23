#ifndef INDEXCOLUMN_H
#define INDEXCOLUMN_H

#include <QDebug>

#include "tablecolumn.h"

class IndexColumn
{
public:
    IndexColumn();

    const TableColumn *getColumn() const;
    void setColumn(const TableColumn *value);

    int getLength() const;
    void setLength(int value);

    bool operator==(IndexColumn &other) const;

private:
    const TableColumn *column;
    int length;
};

QDebug operator<<(QDebug debug, const IndexColumn &ic);

#endif // INDEXCOLUMN_H
