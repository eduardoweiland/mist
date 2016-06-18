#include "queryexplain.h"

QueryExplain::QueryExplain(QSqlQuery &result)
{
    while (result.next()) {
        m_items.append(QueryExplainItem(result.record()));
    }
}

QString QueryExplain::debug() const
{
    QString msg;
    foreach (QueryExplainItem item, m_items) {
        msg += item.debug() + "\n";
    }
    return msg;
}
