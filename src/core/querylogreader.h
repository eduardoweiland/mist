#ifndef SQLLOGREADER_H
#define SQLLOGREADER_H

#include <QList>
#include <QXmlStreamReader>

#include "../entity/query.h"
#include "abstractxmlreader.h"

class QueryLogReader : public AbstractXmlReader
{
public:
    QueryLogReader();
    virtual ~QueryLogReader();

    bool parse(QIODevice *file);

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
