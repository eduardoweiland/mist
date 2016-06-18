#include <QVariant>

#include "queryexplainitem.h"

QueryExplainItem::QueryExplainItem(const QSqlRecord &record)
{
    selectType = record.value("select_type").toString();
    table = record.value("table").toString();
    type = record.value("type").toString();
    possibleKeys = record.value("possible_keys").toString();
    key = record.value("key").toString();
    keyLength = record.value("key_len").toString();
    ref = record.value("ref").toString();
    rows = record.value("rows").toULongLong();
    extra = record.value("Extra").toString();
}

QString QueryExplainItem::debug() const
{
    QString msg = QString("| %1 | %2 | %3 | %4 | %5 | %6 | %7 | %8 | %9")
            .arg(selectType)
            .arg(table)
            .arg(type)
            .arg(possibleKeys)
            .arg(key)
            .arg(keyLength)
            .arg(ref)
            .arg(rows)
            .arg(extra);

    return msg;
}
