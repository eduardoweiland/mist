#ifndef QUERYEXPLAIN_H
#define QUERYEXPLAIN_H

#include <QList>
#include <QSqlQuery>

#include "queryexplainitem.h"

class QueryExplain
{
public:
    QueryExplain(QSqlQuery &result);

    QString debug() const;

private:
    QList<QueryExplainItem> m_items;
};

#endif // QUERYEXPLAIN_H
