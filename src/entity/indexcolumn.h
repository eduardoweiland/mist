#ifndef INDEXCOLUMN_H
#define INDEXCOLUMN_H

#include <QDebug>

#include "tablecolumn.h"

class IndexColumn
{
public:
    IndexColumn();

    const QString getColumn() const;
    void setColumn(const QString value);

    int getLength() const;
    void setLength(int value);

    bool operator==(IndexColumn &other) const;
    bool operator==(const IndexColumn &other) const;

private:
    QString column;
    int length;
};

QDebug operator<<(QDebug debug, const IndexColumn &ic);

#endif // INDEXCOLUMN_H
