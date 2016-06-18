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

    QList<Table> getTables() const;
    void setTables(const QList<Table> &tables);
    void addTable(Table &table);
    Table* getTable(QString name);

    QList<Query> getQueries() const;
    void setQueries(const QList<Query> &queries);
    void addQuery(const Query &query);

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
