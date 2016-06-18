#ifndef SCHEMA_H
#define SCHEMA_H

#include <QDebug>
#include <QList>
#include <QMap>

#include "candidateindex.h"
#include "query.h"
#include "table.h"

class MistProject
{
public:
    MistProject();
    MistProject(MistProject &other);

    QList<Table> getTables() const;
    void setTables(const QList<Table> &tables);
    void addTable(Table &table);
    Table* getTable(const QString name);

    QList<Query> getQueries() const;
    void setQueries(const QList<Query> &queries);
    void addQuery(const Query &query);
    Query *getQuery(const int id);

    QList<CandidateIndex> getCandidates() const;
    void setCandidates(const QList<CandidateIndex> &candidates);
    void addCandidate(const CandidateIndex &candidate);

private:
    QMap<QString, Table> m_mapTables;
    QList<Query> m_queries;
    QList<CandidateIndex> m_candidates;
};

QDebug operator<<(QDebug debug, const MistProject &project);

#endif // SCHEMA_H
