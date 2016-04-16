#ifndef SQLLOGREADER_H
#define SQLLOGREADER_H

#include <QList>
#include <QXmlStreamReader>

#include "../entity/query.h"

class QueryLogReader
{
public:
    QueryLogReader();
    virtual ~QueryLogReader();

    bool parse(QFile *file);
    QString getError() const;

    const QList<Query>& getQueries() const;

private:
    QList<Query> queries;
    QXmlStreamReader xml;

    void readQueries();
    void readQuery();
    void readJoins(Query *query);
    void readJoinConditions(JoinTable *join);
    void readWhere(Query *query);
    void readOrderBy(Query *query);
    void readGroupBy(Query *query);
};

#endif // SQLLOGREADER_H
