#include <QFile>

#include "querylogreader.h"

QueryLogReader::QueryLogReader() :
    AbstractXmlReader()
{
}

QueryLogReader::~QueryLogReader()
{
}

const QList<Query>& QueryLogReader::getQueries() const
{
    return this->queries;
}

bool QueryLogReader::parse(QIODevice *file)
{
    xml.setDevice(file);

    if (xml.readNextStartElement()) {
        if (xml.name() == "queries" && xml.attributes().value("version") == "1.0") {
            readQueries();
        }
        else {
            xml.raiseError(QObject::tr("The file is not a valid MIST Query Log File."));
        }
    }

    return !xml.error();
}

void QueryLogReader::readQueries()
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "queries");

    while (xml.readNextStartElement()) {
        if (xml.name() == "query") {
            readQuery();
        }
        else {
            xml.raiseError(QObject::tr("Unknown tag found: %1").arg(xml.name().toString()));
        }
    }
}

void QueryLogReader::readQuery()
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "query");

    Query query;

    query.setId(xml.attributes().value("id").toInt());
    query.setCount(xml.attributes().value("count").toInt());

    while (xml.readNextStartElement()) {
        if (xml.name() == "from") {
            query.setFrom(xml.readElementText());
        }
        else if (xml.name() == "joins") {
            readJoins(&query);
        }
        else if (xml.name() == "where") {
            readWhere(&query);
        }
        else if (xml.name() == "orderby") {
            readOrderBy(&query);
        }
        else if (xml.name() == "groupby") {
            readGroupBy(&query);
        }
        else {
            xml.raiseError(QObject::tr("Unknown tag found: %1").arg(xml.name().toString()));
        }
    }

    queries.append(query);
}

void QueryLogReader::readJoins(Query *query)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "joins");
    Q_ASSERT(query != nullptr);

    while (xml.readNextStartElement()) {
        if (xml.name() == "join") {
            JoinTable join;
            join.setTable(xml.attributes().value("table").toString());

            if (xml.attributes().value("type") == "inner") {
                join.setType(JoinTable::INNER);
            }
            else if (xml.attributes().value("type") == "left") {
                join.setType(JoinTable::LEFT);
            }
            else if (xml.attributes().value("type") == "right") {
                join.setType(JoinTable::RIGHT);
            }
            else {
                xml.raiseError(QObject::tr("Invalid join type found: %1").arg(xml.attributes().value("type").toString()));
            }

            readJoinConditions(&join);

            query->addJoin(join);
        }
        else {
            xml.raiseError(QObject::tr("Unknown tag found: %1").arg(xml.name().toString()));
        }
    }
}

void QueryLogReader::readJoinConditions(JoinTable *join)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "join");
    Q_ASSERT(join != nullptr);

    while (xml.readNextStartElement()) {
        if (xml.name() == "condition") {
            FilterCondition condition;
            condition.setTable(join->getTable());
            condition.setField(xml.attributes().value("field").toString());

            if (xml.attributes().value("type") == "exactmatch") {
                condition.setType(FilterCondition::EXACTMATCH);
            }
            else if (xml.attributes().value("type") == "range") {
                condition.setType(FilterCondition::RANGE);
            }
            else if (xml.attributes().value("type") == "list") {
                condition.setType(FilterCondition::LIST);
            }
            else if (xml.attributes().value("type") == "like") {
                condition.setType(FilterCondition::LIKE);
            }
            else {
                xml.raiseError(QObject::tr("Invalid join condition type found: %1").arg(xml.attributes().value("type").toString()));
            }

            join->addCondition(condition);
            xml.skipCurrentElement();
        }
        else {
            xml.raiseError(QObject::tr("Unknown tag found: %1").arg(xml.name().toString()));
        }
    }
}

void QueryLogReader::readWhere(Query *query)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "where");
    Q_ASSERT(query != nullptr);

    while (xml.readNextStartElement()) {
        if (xml.name() == "condition") {
            FilterCondition condition;
            condition.setTable(xml.attributes().value("table").toString());
            condition.setField(xml.attributes().value("field").toString());

            if (xml.attributes().value("type") == "exactmatch") {
                condition.setType(FilterCondition::EXACTMATCH);
            }
            else if (xml.attributes().value("type") == "range") {
                condition.setType(FilterCondition::RANGE);
            }
            else if (xml.attributes().value("type") == "list") {
                condition.setType(FilterCondition::LIST);
            }
            else if (xml.attributes().value("type") == "like") {
                condition.setType(FilterCondition::LIKE);
            }
            else {
                xml.raiseError(QObject::tr("Invalid where condition type found: %1").arg(xml.attributes().value("type").toString()));
            }

            query->addWhere(condition);
            xml.skipCurrentElement();
        }
        else {
            xml.raiseError(QObject::tr("Unknown tag found: %1").arg(xml.name().toString()));
        }
    }
}

void QueryLogReader::readOrderBy(Query *query)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "orderby");
    Q_ASSERT(query != nullptr);

    while (xml.readNextStartElement()) {
        if (xml.name() == "field") {
            OrderByField orderBy;
            orderBy.setTable(xml.attributes().value("table").toString());
            orderBy.setField(xml.attributes().value("field").toString());

            if (xml.attributes().value("dir") == "asc") {
                orderBy.setDir(OrderByField::ASC);
            }
            else if (xml.attributes().value("dir") == "desc") {
                orderBy.setDir(OrderByField::DESC);
            }
            else {
                xml.raiseError(QObject::tr("Invalid order by direction found: %1").arg(xml.attributes().value("dir").toString()));
            }

            query->addOrderBy(orderBy);
            xml.skipCurrentElement();
        }
        else {
            xml.raiseError(QObject::tr("Unknown tag found: %1").arg(xml.name().toString()));
        }
    }
}

void QueryLogReader::readGroupBy(Query *query)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "groupby");
    Q_ASSERT(query != nullptr);

    while (xml.readNextStartElement()) {
        if (xml.name() == "field") {
            GroupByField groupBy;
            groupBy.setTable(xml.attributes().value("table").toString());
            groupBy.setField(xml.attributes().value("field").toString());
            query->addGroupBy(groupBy);
            xml.skipCurrentElement();
        }
        else {
            xml.raiseError(QObject::tr("Unknown tag found: %1").arg(xml.name().toString()));
        }
    }
}
