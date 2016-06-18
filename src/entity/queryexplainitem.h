#ifndef QUERYEXPLAINITEM_H
#define QUERYEXPLAINITEM_H

#include <QSqlRecord>

class QueryExplainItem
{
public:
    QueryExplainItem(const QSqlRecord &record);

    QString debug() const;

private:
    QString selectType;
    QString table;
    QString type;
    QString possibleKeys;
    QString key;
    QString keyLength;
    QString ref;
    qulonglong rows;
    QString extra;
};

#endif // QUERYEXPLAINITEM_H
